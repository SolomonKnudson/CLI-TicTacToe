#include "tictactoe.h"
#include<sstream>
//TODO: continue testing different board sizes.

int main(int argc, char *argv[])
{
    std::string testyTest{ "a" };
    try
    {
        std::stoi(testyTest);
    }
    catch (const std::exception& error)
    {
        std::cout << error.what() << '\n';
    }
    int playerX{-1};
    int playerO {-2};

    Board test{5,  5};
//    test.setsBoard(53, 53);
    test.display(playerX, playerO);
    //test.setLateralWin(2916, playerO);
//    test.coverBoardSlot(1, -2);
    //test.setDiagonalWin(53, playerO, true);
    //test.setVerticalWin(55, playerO);
    test.display(playerX, playerO);
//    test.display(playerX, playerO);
//    test.clearWinConfiguration(playerO);
//    test.display(playerX, playerO);
    //test.clearWinConfiguration(playerO);
    test.display(playerX, playerO);
    if(test.isTie(-1, -2))
    {
        std::cout << "Tie!\n";
    }
    else if(test.isWinningMove(-2))
    {
        std::cout << "Win case: " << test.winCase() << '\n';
    }
    TicTacToe ticTacToe{};
    return 0;
}
