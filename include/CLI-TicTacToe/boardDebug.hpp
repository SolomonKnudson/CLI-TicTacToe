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
    //util methods for board debugging
    void
    setDiagonalWinEvenBoard(Board& board, char playerMark, bool reverseWin);

    void
    setDiagonalWinLopsidedRow(Board& board,
                              int startColumn,
                              char playerMark,
                              bool reverseWin);

    void
    setDiagonalWinLopsidedColumn(Board& board,
                                 int startRow,
                                 char playerMark,
                                 bool reverseWin);

    struct ValidWinCases
    {
      std::vector<int> m_lateralCases{};
      std::vector<int> m_verticalCases{};
      std::vector<int> m_diagonalCases{};
    };

    static bool diagonalReverseWin{};

    bool
    isValidWinCase(Board& board,
                   int startPoint,
                   BoardTypes::WinCase winCase,
                   bool reverseWin = false);

    bool
    isValidWin(const std::vector<int>& winCases, int startPoint);

    bool
    isValidDiagonalWin(const std::vector<int>& winCases,
                       int startPoint,
                       bool reverseWin = false);

    //Util methods for isValidWinCase()
    void
    recalculateWinCases(const Board& board, ValidWinCases& winCases);

    std::vector<int>
    validLateralWinCases(const Board& board);

    std::vector<int>
    validVerticalWinCases(const Board& board);

    std::vector<int>
    validDiagonalWinCases(const Board& board);

    //Util mehods for clearWinConFig()
    void
    clearLateralWin(Board& board, char playerMark);

    void
    clearVerticalWin(Board& board, char playerMark);

    void
    clearDiagonalWin(Board& board, char playerMark);

    //Util for clearDiaWin();
    void
    clearDiagonalWinEvenBoard(Board& board, char playerMark);

    void
    clearDiagonalWinLopsidedRow(Board& board, char playerMark);

    void
    clearDiagonalWinLopsidedColumn(Board& board, char playerMark);

    bool
    multipleWinCases(const Board& board, char playerMark);
  }    // namespace util
};     // namespace BoardDebug
#endif // CLI_TICTACTOE_BOARD_DEBUG_H
