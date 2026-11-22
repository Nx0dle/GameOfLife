#include <cstdlib>
#include <ctime>
#include <string>

#include "Board.hpp"

Board::Board(int boardSize) {
    size = boardSize;
    board.resize(boardSize, std::vector<bool>(boardSize, 0));
}

void Board::DrawASCII() const {
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

void Board::GenerateRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            board[row][col] = (std::rand() % 2 == 1);
        }
    }
}

bool Board::IsOutsideBorder(Point point) {
    if (point.x < 0 || point.y < 0) return true;
    if (point.x > (size - 1) || point.y > (size - 1)) return true;

    return false;
}