#include "tictactoe.h"

int main(int argc, char *argv[])
{
    char playerX{ 'X' };
    char playerO{ 'O' };
    Board testBoard{12, 12};
    testBoard.setDiagonalWin(-999, playerX);
    testBoard.display();
    testBoard.clearWinConfiguration(playerX);
    testBoard.display();
    TicTacToe ticTacToe{};
    return 0;
}
