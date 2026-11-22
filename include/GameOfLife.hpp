#include <vector>

#include "Board.hpp"

class GameOfLife {
    public:
        Board gameBoard;

        GameOfLife(int boardSize);

        int CountNeighbours(Point point);
        void CellStep();
        bool AliveOrDead(bool cell, int neighbourCount);
};