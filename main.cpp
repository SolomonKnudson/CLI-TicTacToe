#include "tictactoe.h"



//TODO: continue testing different board size.

int main(int argc, char *argv[])
{
    Board test{30, 12};
    test.display(-1, -2);
    test.setLateralWin(241, -2);
    test.setVerticalWin(1, -2);
    test.setDiagonalWin(217, -2);
//    test.setTie(-2);
    test.display(-1, -2);

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
