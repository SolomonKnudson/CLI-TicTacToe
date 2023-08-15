#include "tictactoe.h"



//TODO: continue testing different board sizes.

int main(int argc, char *argv[])
{
    int playerX{-1};
    int playerO {-2};
    Board test{19,  19};
    test.display(playerX, playerO);
//    test.setLateralWin(1, playerO);
//    test.display(playerX, playerO);
    test.setDiagonalWin(37, playerO);
//    test.display(playerX, playerO);
//    test.clearWinConfiguration(playerO);
//    test.setVerticalWin(1, playerO);
//    test.display(playerX, playerO);
//    test.clearWinConfiguration(playerO);
    test.display(playerX, playerO);
    if(test.isTie(-1, -2))
    {
        std::cout << "Tie!\n";
    }
    else if(test.isWinningMove(-2))
    {
        std::cout << "Win case: " << test.winCase() << '\n';
    }
//    TicTacToe ticTacToe{};
    return 0;
}
