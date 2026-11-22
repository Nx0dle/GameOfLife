#include <cstdio>
#include <atomic>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "GameOfLife.hpp"

static Uint32 SDLCALL QueueCellStep(void* userdata, SDL_TimerID, Uint32 interval) {
    SDL_Event event{};
    event.type = 1;
    SDL_PushEvent(&event);

    auto* actualInterval = static_cast<std::atomic<Uint32>*>(userdata);

    return actualInterval->load();
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game of Life", 640, 640, 0);
    if (!window) {
        std::fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GameOfLife game(32);
    game.gameBoard.GenerateRandom();
    game.gameBoard.Draw(renderer);

    bool gamepaused = false;
    
    std::atomic<Uint32> intervalMs{1000};
    const SDL_TimerID timer = SDL_AddTimer(1000, QueueCellStep, &intervalMs);
    if (timer == 0) {
        std::fprintf(stderr, "SDL_AddTimer: %s\n", SDL_GetError());
    }

    SDL_Event event;
    int result = 0;

    while (true) {
        if (!SDL_WaitEvent(&event)) {
            std::fprintf(stderr, "SDL_WaitEvent: %s\n", SDL_GetError());
            result = 1;
            break;
        }

        if (event.type == SDL_EVENT_QUIT) {
            break;
        }

        if (event.type == 1 && !gamepaused) {
            game.CellStep();
            game.gameBoard.Draw(renderer);
        }

        if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
            if (event.key.key == SDLK_UP && intervalMs.load() > 100) {
                if (gamepaused) continue;
                intervalMs.fetch_sub(100);
            } else if (event.key.key == SDLK_DOWN) {
                if (gamepaused) continue;
                intervalMs.fetch_add(100);
            } else if (event.key.key == SDLK_SPACE) {
                gamepaused = !gamepaused;
            }
        }
    }

    if (timer != 0) {
        SDL_RemoveTimer(timer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return result;
}
