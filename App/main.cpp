#include <CLI-TicTacToe/boardDebug.hpp>
#include <CLI-TicTacToe/tictactoe.hpp>
#include <iostream>

int
main(int argc, char* argv[])
{
  //Starter code for testing different board sizes
  char playerO{'O'};
  char playerX{'X'};

  Board testBoard{15, 15};
  testBoard.display();

  BoardDebug::setDiagonalWin(testBoard, 8, playerX, true);
  testBoard.display();

  if (testBoard.isWinningMove(playerX))
  {
    std::cout << "|Win Case: " << testBoard.winCaseToString() << '\n';
  }

  BoardDebug::clearWinConfiguration(testBoard, playerX);
  testBoard.display();

  TicTacToe ticTacToe{};
  return 0;
}
