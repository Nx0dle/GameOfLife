#include "GameOfLife.hpp"

int main() {
    const int boardSize = 10;
    GameBoard testBoard = {{0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0},
                           {1, 1, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0}};
    GameBoard board = generateRandomBoard(boardSize);

    drawBoard(testBoard);

    for (int i = 0; i < 4; i++) {
        testBoard = cellStep(testBoard);
        drawBoard(testBoard);
    }
}
