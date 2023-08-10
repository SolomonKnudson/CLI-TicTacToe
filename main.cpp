#include "tictactoe.h"



//TODO: continue testing different board size.

int main(int argc, char *argv[])
{
    Board test{14, 17};

    test.display(-1, -2);
//    test.setLateralWin(1, -2);
//    test.setVerticalWin(9, -2);
    test.setDiagonalWin(4, -2);
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
