#include <vector>

typedef std::vector<std::vector<bool>> GameBoard;

typedef struct {
    int x;
    int y;
} Point;

void drawBoard(const GameBoard &board);
GameBoard generateRandomBoard(const int size);
int countNeighbours(Point point, GameBoard &board);
bool isBorder(Point point, int boardSize);
GameBoard cellStep(GameBoard board);
bool aliveOrDead(bool cell, int neighbourCount);