#include "tictactoe.h"

int main(int argc, char *argv[])
{
    Board test{15, 11};
    test.setDiagonalWin(11, -2, true);
    test.display(-1, -2);
//    TicTacToe ticTacToe{};
    return 0;
}
