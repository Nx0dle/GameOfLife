#include <vector>
#include <cstdio>

#include <SDL3/SDL_render.h>

typedef struct {
    int x;
    int y;
} Point;

struct SDL_Renderer;

class Board {
    public:
        int size;
        std::vector<std::vector<bool>> board;

        Board(int size);

        void DrawASCII() const;
        void Draw(SDL_Renderer *renderer) const;
        void GenerateRandom();
        bool IsOutsideBorder(Point point);
};