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
    const GameBoard start = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    };

    const auto afterTwoSteps = cellStep(cellStep(start));

    return afterTwoSteps == start;
}

bool testBlock() {
    const GameBoard start = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    return cellStep(start) == start;
}

bool testGlider() {
    const GameBoard start = {{0, 1, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 1, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0}};

    const GameBoard expected = {{0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 1, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 1, 0, 0, 0, 0},
                                      {0, 1, 1, 1, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0}};

    const auto afterFourSteps = cellStep(cellStep(cellStep(cellStep(start))));

    return afterFourSteps == expected;
}