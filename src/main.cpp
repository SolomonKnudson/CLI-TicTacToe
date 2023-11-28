#include "tictactoe.h"

int main(int argc, char *argv[])
{
    char playerX{ 'X' };
    char playerO{ 'O' };
    Board testBoard{35, 45};
    testBoard.display();
    testBoard.setDiagonalWin(10, playerX);
    testBoard.display();
    testBoard.clearWinConfiguration(playerX);
    testBoard.display();
    TicTacToe ticTacToe{};
    return 0;
}
