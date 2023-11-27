#include "tictactoe.h"
#include "board.h"
#include <vector>



int main(int argc, char *argv[])
{
    char playerX{ 'X'};
    char playerO{ 'O'};
    Board testBoard{};
    testBoard.display();
    testBoard.setDiagonalWin(1, playerX);
    testBoard.display();
    testBoard.clearWinConfiguration(playerX);
    testBoard.display();
    TicTacToe ticTacToe{};
    return 0;
}
