#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

#include "GameOfLife.hpp"

void drawBoard(const GameBoard &board) {
    std::string horizontalBorder;
    for (std::size_t column = 0; column < board.front().size(); ++column) {
        horizontalBorder += "+---";
    }
    horizontalBorder += '+';

    for (const auto& row : board) {
        std::puts(horizontalBorder.c_str());
        for (bool cell : row) {
            std::printf("| %c ", cell ? '#' : ' ');
        }
        std::puts("|");
    }
    std::puts(horizontalBorder.c_str());
}

GameBoard generateRandomBoard(const int size) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameBoard board(size, std::vector<bool>(size, 0));

    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            board[row][col] = (std::rand() % 2 == 1);
        }
    }

    return board;
}

int countNeighbours(Point point, GameBoard &board) {
    int neighbourCount = 0;

    for (int row = (point.x - 1); row <= (point.x + 1); row++) {
        for (int col = (point.y - 1); col <= (point.y + 1); col++) {
            if (row == point.x && col == point.y) continue;
            if (isBorder({row, col}, board.size())) continue;
            if (board[row][col]) neighbourCount++;
        }
    }

    return neighbourCount;
}

bool isBorder(Point point, int boardSize) {
    if (point.x < 0 || point.y < 0) return true;
    if (point.x > (boardSize - 1) || point.y > (boardSize - 1)) return true;

    return false;
}

GameBoard cellStep(GameBoard board) {
    Point currentPoint;
    GameBoard nextBoard(board.size(), std::vector<bool>(board.size(), 0));

    for (int x = 0; x < board.size(); x++) {
        for (int y = 0; y < board[x].size(); y++) {
            currentPoint = {x, y};
            int neighboursCount = countNeighbours(currentPoint, board);

            bool cellState = aliveOrDead(board[x][y], neighboursCount);
            nextBoard[x][y] = cellState;
        }
    }

    return nextBoard;
}

bool aliveOrDead(bool cell, int neighbourCount) {
    if (cell && neighbourCount < 2) return false;
    if (cell && (neighbourCount == 2 || neighbourCount == 3)) return true;
    if (cell && neighbourCount > 3) return false;
    if (!cell && neighbourCount == 3) return true;

    return false;
}
