#include "GameOfLife.hpp"

GameOfLife::GameOfLife(int boardSize) 
    : gameBoard(boardSize) {}

int GameOfLife::CountNeighbours(Point point) {
    int neighbourCount = 0;

    for (int row = (point.x - 1); row <= (point.x + 1); row++) {
        for (int col = (point.y - 1); col <= (point.y + 1); col++) {
            if (row == point.x && col == point.y) continue;
            if (gameBoard.IsOutsideBorder({row, col})) continue;
            if (gameBoard.board[row][col]) neighbourCount++;
        }
    }

    return neighbourCount;
}

void GameOfLife::CellStep() {
    Point currentPoint;
    
    Board nextGameBoard = gameBoard;

    for (int x = 0; x < gameBoard.board.size(); x++) {
        for (int y = 0; y < gameBoard.board[x].size(); y++) {
            currentPoint = {x, y};
            int neighboursCount = CountNeighbours(currentPoint);

            bool cellState = AliveOrDead(gameBoard.board[x][y], neighboursCount);
            nextGameBoard.board[x][y] = cellState;
        }
    }

    gameBoard = nextGameBoard;
}

bool GameOfLife::AliveOrDead(bool cell, int neighbourCount) {
    if (cell && neighbourCount < 2) return false;
    if (cell && (neighbourCount == 2 || neighbourCount == 3)) return true;
    if (cell && neighbourCount > 3) return false;
    if (!cell && neighbourCount == 3) return true;

    return false;
}
