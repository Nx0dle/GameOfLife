#include <SDL3/SDL_main.h>

#include "GameOfLife.hpp"

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

        if (event.type == SDL_EVENT_KEY_DOWN &&
            event.key.key == SDLK_SPACE && !event.key.repeat) {
            game.CellStep();
            game.gameBoard.Draw(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return result;
}
