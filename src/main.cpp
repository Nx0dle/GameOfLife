#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

void drawBoard(std::vector<std::vector<bool>> &board);
std::vector<std::vector<bool>> generateRandomBoard(const int size);

int main() {
    const int boardSize = 10;
    std::vector<std::vector<bool>> board = generateRandomBoard(boardSize);

    drawBoard(board);
}

void drawBoard(std::vector<std::vector<bool>> &board) {
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

std::vector<std::vector<bool>> generateRandomBoard(const int size) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<std::vector<bool>> board(size, std::vector<bool>(size, 0));

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] = (std::rand() % 2 == 1);
        }
    }

    return board;
}
