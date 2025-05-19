#include <CLI-TicTacToe/boardDebug.hpp>

using namespace BoardTypes;
namespace BoardDebug
{
  namespace util
  {
    //Util methods for all win case set'ers
    bool
    isValidWinCase(Board& board,
                   const int startPoint,
                   const WinCase winCase,
                   const bool reverseWin)
    {
      static ValidWinCases winCases{validLateralWinCases(board),
                                    validVerticalWinCases(board),
                                    validDiagonalWinCases(board)};
      int rows{board.rows()};
      int columns{board.columns()};

      static int previousRow{rows};
      static int previousColumn{columns};

      if (previousRow != rows || previousColumn != columns)
      {
        previousRow = rows;
        previousColumn = columns;
        recalculateWinCases(board, winCases);
      }

      switch (winCase)
      {
        case WinCase::Lateral:
          return isValidWin(winCases.m_lateralCases, startPoint);

        case WinCase::Vertical:
          return isValidWin(winCases.m_verticalCases, startPoint);

        case WinCase::Diagonal:
          return isValidDiagonalWin(
              winCases.m_diagonalCases, startPoint, reverseWin);

        case WinCase::NoWinCase:
          break;
      }

      return false;
    }

    //Util methods for isValidWinCase
    void
    recalculateWinCases(const Board& board, ValidWinCases& winCases)
    {
      winCases.m_lateralCases.clear();
      winCases.m_verticalCases.clear();
      winCases.m_diagonalCases.clear();

      winCases.m_lateralCases = validLateralWinCases(board);
      winCases.m_verticalCases = validVerticalWinCases(board);
      winCases.m_diagonalCases = validDiagonalWinCases(board);
    }

    bool
    isValidWin(const std::vector<int>& winCases, const int startPoint)
    {
      for (const int winCase : winCases)
      {
        if (winCase == startPoint)
        {
          return true;
        }
      }

      return false;
    }

    bool
    isValidDiagonalWin(const std::vector<int>& winCases,
                       const int startPoint,
                       const bool reverseWin)
    {
      const int n{static_cast<int>(winCases.size())};
      const int offSet{n / 2};

      if (!reverseWin)
      {
        for (int i{0}; i < offSet; ++i)
        {
          if (winCases[i] == startPoint)
          {
            return true;
          }
        }
      }
      //reverse cases will always be the last [offset] number of elements in vec
      // offset to vec size
      else
      {
        for (int i{offSet}; i < n; ++i)
        {
          if (winCases[i] == startPoint)
          {
            return true;
          }
        }
      }

      return false;
    }

    std::vector<int>
    validLateralWinCases(const Board& board)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      const Table& table{board.cInternalTable()};
      std::vector<int> winCases{};

      for (int row{0}; row < rows; ++row)
      {
        winCases.push_back(table[row][0].m_piecePosition);
      }

      return winCases;
    }

    std::vector<int>
    validVerticalWinCases(const Board& board)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      const Table& table{board.cInternalTable()};
      std::vector<int> winCases{};

      for (int column{0}; column < columns; ++column)
      {
        winCases.push_back(table[0][column].m_piecePosition);
      }

      return winCases;
    }

    std::vector<int>
    validDiagonalWinCases(const Board& board)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      const Table& table{board.cInternalTable()};
      std::vector<int> winCases{};

      int offSet{};

      if (rows < columns)
      {
        offSet = columns - rows;
        for (int i{0}; i <= offSet; ++i)
        {
          winCases.push_back(table[0][i].m_piecePosition);
        }

        //reverse cases
        for (int i{0}; i <= offSet; ++i)
        {
          winCases.push_back(
              table[0][static_cast<size_t>((columns - 1) - i)].m_piecePosition);
        }
      }
      else if (columns < rows)
      {
        offSet = rows - columns;
        for (int i{0}; i <= offSet; ++i)
        {
          winCases.push_back(table[i][0].m_piecePosition);
        }

        //reverse Cases
        for (int i{0}; i <= offSet; ++i)
        {
          winCases.push_back(
              table[i][static_cast<size_t>(columns - 1)].m_piecePosition);
        }
      }

      return winCases;
    }
  } // namespace util
} // namespace BoardDebug
