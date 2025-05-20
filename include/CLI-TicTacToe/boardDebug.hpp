#ifndef CLI_TICTACTOE_BOARD_DEBUG_H
#define CLI_TICTACTOE_BOARD_DEBUG_H
#include <CLI-TicTacToe/board.hpp>
#include <vector>

namespace BoardDebug
{
  bool
  setLateralWin(Board& board, int row, char playerMark);

  bool
  setVerticalWin(Board& board, int column, char playerMark);

  bool
  setDiagonalWin(Board& board,
                 int startPoint,
                 char playerMark,
                 bool reverseWin = false);

  bool
  setTie(Board& board, char playerMark);

  void
  clearWinConfiguration(Board& board, char playerMark);

  namespace util
  {
    //Util mehods for clearWinConFig()
    void
    clearLateralWin(Board& board, char playerMark);

    void
    clearVerticalWin(Board& board, char playerMark);

    void
    clearDiagonalWin(Board& board, char playerMark);
  }    // namespace util
};     // namespace BoardDebug
#endif // CLI_TICTACTOE_BOARD_DEBUG_H
