#include <CLI-TicTacToe/boardDebug.hpp>
#include <debug/boardDebugUtil.hpp>

using namespace BoardTypes;
using namespace BoardDebug::util;

namespace BoardDebug
{
  void
  clearWinConfiguration(Board& board, const char playerMark)
  {
    WinCase winCase{board.winCase()};

    if (winCase == WinCase::NoWinCase)
    {
      return;
    }

    if (multipleWinCases(board, playerMark))
    {
      board.setBoard(board.rows(), board.columns());
      return;
    }

    switch (winCase)
    {
      case WinCase::Lateral:
        clearLateralWin(board, playerMark);
        break;

      case WinCase::Vertical:
        clearVerticalWin(board, playerMark);
        break;

      case WinCase::Diagonal:
        //The work required to undo a single diagonal win case isn't worth
        //the headache. <----- I lied.
        clearDiagonalWin(board, playerMark);
        break;

      case WinCase::NoWinCase:
        return;
    }

    winCase = WinCase::NoWinCase;
  }

  namespace util
  {
    //Util methods for clearWinConfig
    void
    clearLateralWin(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      for (int row{0}; row < rows; ++row)
      {
        if (table[row][0].m_playerFlag == playerMark)
        {
          for (int column{0}; column < columns; ++column)
          {
            if (table[row][column].m_playerFlag == playerMark)
            {
              table[row][column].reset();
            }
          }
        }
      }
    }

    void
    clearVerticalWin(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      for (int startColumn{0}; startColumn < columns; ++startColumn)
      {
        if (table[0][startColumn].m_playerFlag == playerMark)
        {
          for (int row{0}; row < rows; ++row)
          {
            if (table[row][startColumn].m_playerFlag == playerMark)
            {
              table[row][startColumn].reset();
            }
          }
        }
      }
    }

    void
    clearDiagonalWin(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      if (rows < columns)
      {
        clearDiagonalWinLopsidedRow(board, playerMark);
      }
      else if (columns < rows)
      {
        clearDiagonalWinLopsidedColumn(board, playerMark);
      }
      else if (board.isEvenBoard())
      {
        clearDiagonalWinEvenBoard(board, playerMark);
      }
    }

    void
    clearDiagonalWinEvenBoard(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      if (!diagonalReverseWin)
      {
        for (int row{0}, column{0}; row < columns; ++row, ++column)
        {
          if (table[row][column].m_playerFlag == playerMark)
          {
            table[row][column].reset();
          }
        }
      }
      else
      {
        for (int row{0}, columnOffset{columns - 1}; row < columns;
             ++row, --columnOffset)
        {
          if (table[row][columnOffset].m_playerFlag == playerMark)
          {
            table[row][columnOffset].reset();
          }
        }
      }
    }

    void
    clearDiagonalWinLopsidedRow(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      int columnOffSet{columns - rows};

      if (!diagonalReverseWin)
      {
        for (int columnStart{0}; columnStart <= columnOffSet; ++columnStart)
        {
          if (table[0][columnStart].m_playerFlag == playerMark)
          {
            for (int row{0}, column{columnStart}; row < rows; ++row, ++column)
            {
              if (table[row][column].m_playerFlag == playerMark)
              {
                table[row][column].reset();
              }
            }
          }
        }
      }
      else
      {
        for (int column{columns - 1}; column >= ((columns - 1) - columnOffSet);
             column--)
        {
          if (table[0][column].m_playerFlag == playerMark)
          {
            for (int row{0}; row < rows; ++row)
            {
              if (table[row][static_cast<size_t>(column - row)].m_playerFlag ==
                  playerMark)
              {
                table[row][static_cast<size_t>(column - row)].reset();
              }
            }
          }
        }
      }
    }

    void
    clearDiagonalWinLopsidedColumn(Board& board, const char playerMark)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      int rowOffset{rows - columns};

      if (!diagonalReverseWin)
      {
        for (int rowStart{0}; rowStart <= rowOffset; ++rowStart)
        {
          if (table[rowStart][0].m_playerFlag == playerMark)
          {
            for (int row{0}; row < (rows - rowOffset); ++row)
            {
              if (table[static_cast<size_t>(row + rowStart)][row]
                      .m_playerFlag == playerMark)
              {
                table[static_cast<size_t>(row + rowStart)][row].reset();
              }
            }
          }
        }
      }
      else
      {

        for (int rowStart{0}, lastColumn{columns - 1}; rowStart <= rowOffset;
             ++rowStart)
        {
          if (table[rowStart][lastColumn].m_playerFlag == playerMark)
          {
            for (int row{0}; row < (rows - rowOffset); ++row)
            {
              if (table[static_cast<size_t>(row + rowStart)]
                       [static_cast<size_t>(lastColumn - row)]
                           .m_playerFlag == playerMark)
              {
                table[static_cast<size_t>(row + rowStart)]
                     [static_cast<size_t>(lastColumn - row)]
                         .reset();
              }
            }
          }
        }
      }
    }

    bool
    multipleWinCases(const Board& board, const char playerMark)
    {
      int winCaseCount{};

      if (board.isLateralWin(playerMark))
      {
        ++winCaseCount;
      }

      if (board.isVerticalWin(playerMark))
      {
        ++winCaseCount;
      }

      //isDia does a lot of looping, only call if you have to.
      if (winCaseCount == 0)
      {
        return false;
      }
      else if (winCaseCount > 1)
      {
        return true;
      }

      if (board.isDiagonalWin(playerMark))
      {
        ++winCaseCount;
      }

      return winCaseCount > 1;
    }
  } // namespace util
} // namespace BoardDebug
