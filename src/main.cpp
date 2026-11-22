#include "GameOfLife.hpp"

int main() {
    GameOfLife game(10);
    game.gameBoard.GenerateRandom();
    game.gameBoard.DrawASCII();

    game.CellStep();
    game.gameBoard.DrawASCII();
}
