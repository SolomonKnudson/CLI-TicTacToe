#include <iostream>
#include "tictactoe.h"
#include "board.h"

int main(int argc, char *argv[])
{
    //Starter code for testing different board sizes
    char playerO{ 'O' };
    char playerX{ 'X' };

    Board testBoard{4, 12};
    testBoard.display();

    testBoard.setDiagonalWin(8, playerX, true);
    testBoard.display();

    if (testBoard.isWinningMove(playerX))
    {
        std::cout << "|Win Case: " << testBoard.winCase() << '\n';
    }

    testBoard.clearWinConfiguration(playerX);
    testBoard.display();

    TicTacToe ticTacToe{};
    return 0;
}
