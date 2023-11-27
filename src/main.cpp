#include "tictactoe.h"

struct BoardPiece
{
    int piecePosition{};
    char playerFlag{};
    bool playerIsOccupying{};
};



int main(int argc, char *argv[])
{
    int playerX{ -1 };
    int playerO{ -2 };
    Board testBoard{ 5, 5 };
    testBoard.display(playerX, playerO);
    testBoard.setDiagonalWin(1, playerX);
    testBoard.display(playerX, playerO);
    testBoard.clearWinConfiguration(playerX);
    testBoard.display(playerX, playerO);
    TicTacToe ticTacToe{};
    return 0;
}
