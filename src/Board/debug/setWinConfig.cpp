#include <CLI-TicTacToe/boardDebug.hpp>
#include <boardDebugUtil.hpp>
#include <iostream>

using namespace BoardTypes;
using namespace BoardDebug::util;

namespace BoardDebug
{
  bool
  setLateralWin(Board& board, const int startRow, const char playerMark)
  {
    if (!isValidWinCase(board, startRow, WinCase::Lateral))
    {
      std::cout << "setLatWin(): Invalid row!\n";
      return false;
    }

    int rows{board.rows()};
    int columns{board.columns()};

    for (int tablePosition{startRow}, endColumn{startRow + columns};
         tablePosition < endColumn;
         tablePosition++)
    {
      board.coverBoardSlot(tablePosition, playerMark);
    }

    board.setWinCase(WinCase::Lateral);
    return true;
  }

  bool
  setVerticalWin(Board& board, const int startColumn, const char playerMark)
  {
    if (!isValidWinCase(board, startColumn, WinCase::Vertical))
    {
      std::cout << "setVertWin(): Invalid column!\n";
      return false;
    }

    int rows{board.rows()};
    int columns{board.columns()};

    for (int row{0}, columnOffset{startColumn}; row < rows;
         row++, columnOffset += columns)
    {
      board.coverBoardSlot(columnOffset, playerMark);
    }

    board.setWinCase(WinCase::Vertical);
    return true;
  }

  bool
  setTie(Board& board, const char playerMark)
  {
    int boardSize{board.rows() * board.columns()};

    for (int tablePosition{1}; tablePosition <= boardSize; tablePosition++)
    {
      board.coverBoardSlot(tablePosition, playerMark);
    }

    return true;
  }

  bool
  setDiagonalWin(Board& board,
                 const int startColumn,
                 const char playerMark,
                 const bool reverseWin)
  {
    int rows{board.rows()};
    int columns{board.columns()};

    if (isValidWinCase(board, startColumn, WinCase::Diagonal, reverseWin) &&
        !board.isEvenBoard())
    {
      if (rows < columns)
      {
        setDiagonalWinLopsidedRow(board, startColumn, playerMark, reverseWin);
      }
      else if (columns < rows)
      {
        setDiagonalWinLopsidedColumn(
            board, startColumn, playerMark, reverseWin);
      }
    }
    //if winCase is invalid but board is even, winCase isn't needed
    //only reverse case
    else if (board.isEvenBoard())
    {
      setDiagonalWinEvenBoard(board, playerMark, reverseWin);
    }
    else
    {
      std::cout << "setDiaWin(): "
                << ((rows < columns) ? "Invalid Column!\n" : "Invalid Row!\n");
      return false;
    }

    diagonalReverseWin = reverseWin;
    board.setWinCase(WinCase::Diagonal);
    return true;
  }

  namespace util
  {
    //Util methods for setDiaWin
    void
    setDiagonalWinEvenBoard(Board& board,
                            const char playerMark,
                            const bool reverseWin)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      if (!reverseWin)
      {
        for (int row{0}, column{0}; row < rows; ++row, ++column)
        {
          board.coverBoardSlot(table[row][column].m_piecePosition, playerMark);
        }
      }
      else
      {
        //Reverse case
        for (int row{0}, columnOffSet{columns - 1}; row < rows; ++row)
        {
          board.coverBoardSlot(
              table[row][static_cast<size_t>(columnOffSet - row)]
                  .m_piecePosition,
              playerMark);
        }
      }
    }

    void
    setDiagonalWinLopsidedRow(Board& board,
                              int startColumn,
                              const char playerMark,
                              const bool reverseWin)
    {
      //convert to index as columns in the rows are not 0 indexed
      --startColumn;

      int rows{board.rows()};
      int columns{board.columns()};

      Table& table{board.internalTable()};

      if (!reverseWin)
      {
        for (int row{0}, column{startColumn}; row < rows; row++)
        {
          board.coverBoardSlot(
              table[row][static_cast<size_t>(column + row)].m_piecePosition,
              playerMark);
        }
      }
      else
      {
        //Reverse case
        for (int row{0}, column{startColumn}; row < rows; ++row)
        {
          board.coverBoardSlot(
              table[row][static_cast<size_t>(column - row)].m_piecePosition,
              playerMark);
        }
      }
    }

    void
    setDiagonalWinLopsidedColumn(Board& board,
                                 int startRow,
                                 const char playerMark,
                                 const bool reverseWin)
    {
      int rows{board.rows()};
      int columns{board.columns()};

      if (!reverseWin)
      {
        for (int column{0}; column < columns;
             ++column, startRow += (columns + 1))
        {
          board.coverBoardSlot(startRow, playerMark);
        }
      }
      else
      {
        //Reverse case
        for (int column{0}; column < columns;
             ++column, startRow += (columns - 1))
        {
          board.coverBoardSlot(startRow, playerMark);
        }
      }
    }
  } // namespace util
} // namespace BoardDebug
