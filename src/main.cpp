#include "tictactoe.h"
#include "board.h"
#include <vector>



int main(int argc, char *argv[])
{
    char playerX{ 'X'};
    char playerO{ 'O'};
    Board testBoard{55, 55};
    testBoard.display();
    //testBoard.setDiagonalWin(12, playerX);
    //testBoard.setVerticalWin(12, playerX);
    testBoard.setLateralWin(166, playerX);
    testBoard.display();
    testBoard.clearWinConfigurationB(playerX);
    testBoard.display();
    TicTacToe ticTacToe{};
    return 0;
}
