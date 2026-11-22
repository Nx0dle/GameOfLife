#include <vector>
#include <cstdio>

typedef struct {
    int x;
    int y;
} Point;

class Board {
    public:
        int size;
        std::vector<std::vector<bool>> board;

        Board(int size);

        void DrawASCII() const;
        void GenerateRandom();
        bool IsOutsideBorder(Point point);
};