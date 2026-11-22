#include "GameOfLife.hpp"
#include <cstdio>

bool testBlinker();
bool testBlock();
bool testGlider();

int main() {
    const bool blinkerPassed = testBlinker();
    const bool blockPassed = testBlock();
    const bool gliderPassed = testGlider();

    std::printf("Blinker: %s\n", blinkerPassed ? "OK" : "FAIL");
    std::printf("Block: %s\n", blockPassed ? "OK" : "FAIL");
    std::printf("Glider: %s\n", gliderPassed ? "OK" : "FAIL");

    return blinkerPassed && blockPassed && gliderPassed ? 0 : 1;
}

bool testBlinker() {
    GameOfLife game = GameOfLife(3);
    game.gameBoard.board = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    };

    const std::vector<std::vector<bool>> expected = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    };

    game.CellStep();
    game.CellStep();

    return game.gameBoard.board == expected;
}

bool testBlock() {
    GameOfLife game = GameOfLife(4);
    game.gameBoard.board = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    const std::vector<std::vector<bool>> expected = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    game.CellStep();

    return game.gameBoard.board == expected;
}

bool testGlider() {
    GameOfLife game = GameOfLife(8);
    game.gameBoard.board = {{0, 1, 0, 0, 0, 0, 0, 0},
                            {0, 0, 1, 0, 0, 0, 0, 0},
                            {1, 1, 1, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0}};

    const std::vector<std::vector<bool>> expected = {{0, 0, 0, 0, 0, 0, 0, 0},
                                                     {0, 0, 1, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 1, 0, 0, 0, 0},
                                                     {0, 1, 1, 1, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0, 0, 0}};

    game.CellStep();
    game.CellStep();
    game.CellStep();
    game.CellStep();

    return game.gameBoard.board == expected;
}