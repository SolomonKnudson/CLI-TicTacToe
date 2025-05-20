#ifndef CLI_TICTACTOE_DEBUG_UTIL_H
#define CLI_TICTACTOE_DEBUG_UTIL_H
#include <CLI-TicTacToe/board.hpp>

namespace BoardDebug
{
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

    inline bool diagonalReverseWin{};

    bool
    isValidWinCase(Board& board,
                   int startPoint,
                   BoardTypes::WinCase winCase,
                   bool reverseWin = false);

    //Util methods for isValidWinCase()
    bool
    isValidWin(const std::vector<int>& winCases, int startPoint);

    bool
    isValidDiagonalWin(const std::vector<int>& winCases,
                       int startPoint,
                       bool reverseWin = false);

    void
    recalculateWinCases(const Board& board, ValidWinCases& winCases);

    std::vector<int>
    validLateralWinCases(const Board& board);

    std::vector<int>
    validVerticalWinCases(const Board& board);

    std::vector<int>
    validDiagonalWinCases(const Board& board);

    //Util for clearDiaWin();
    void
    clearDiagonalWinEvenBoard(Board& board, char playerMark);

    void
    clearDiagonalWinLopsidedRow(Board& board, char playerMark);

    void
    clearDiagonalWinLopsidedColumn(Board& board, char playerMark);

    bool
    multipleWinCases(const Board& board, char playerMark);
  } // namespace util
} // namespace BoardDebug
#endif // CLI_TICTACTOE_DEBUG_UTIL_H
