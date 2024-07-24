#include "board.hpp"

#ifdef BOARD_DEBUG
using namespace BoardTypes;

void
Board::clearWinConfiguration(const char playerMark)
{
  if (m_winCase == WinCase::NoWinCase)
  {
    return;
  }

  if (_multipleWinCases(playerMark))
  {
    setBoard(m_rows, m_columns);
    return;
  }

  switch (m_winCase)
  {
    case WinCase::Lateral:
      _clearLateralWin(playerMark);
      break;

    case WinCase::Vertical:
      _clearVerticalWin(playerMark);
      break;

    case WinCase::Diagonal:
      //The work required to undo a single diagonal win case isn't worth
      //the headache. <----- I lied.
      _clearDiagonalWin(playerMark);
      break;

    case WinCase::NoWinCase:
      return;
  }

  m_winCase = WinCase::NoWinCase;
}

//Util methods for clearWinConfig
void
Board::_clearLateralWin(const char playerMark)
{
  for (int row{0}; row < m_rows; ++row)
  {
    if (m_table[row][0].m_playerFlag == playerMark)
    {
      for (int column{0}; column < m_columns; ++column)
      {
        if (m_table[row][column].m_playerFlag == playerMark)
        {
          m_table[row][column].reset();
        }
      }
    }
  }
}

void
Board::_clearVerticalWin(const char playerMark)
{
  for (int startColumn{0}; startColumn < m_columns; ++startColumn)
  {
    if (m_table[0][startColumn].m_playerFlag == playerMark)
    {
      for (int row{0}; row < m_rows; ++row)
      {
        if (m_table[row][startColumn].m_playerFlag == playerMark)
        {
          m_table[row][startColumn].reset();
        }
      }
    }
  }
}

void
Board::_clearDiagonalWin(const char playerMark)
{
  if (m_rows < m_columns)
  {
    _clearDiagonalWinLopsidedRow(playerMark);
  }
  else if (m_columns < m_rows)
  {
    _clearDiagonalWinLopsidedColumn(playerMark);
  }
  else if (m_evenBoard)
  {
    _clearDiagonalWinEvenBoard(playerMark);
  }
}

void
Board::_clearDiagonalWinEvenBoard(const char playerMark)
{
  if (!m_diagonalReverseWin)
  {
    for (int row{0}, column{0}; row < m_columns; ++row, ++column)
    {
      if (m_table[row][column].m_playerFlag == playerMark)
      {
        m_table[row][column].reset();
      }
    }
  }
  else
  {
    for (int row{0}, columnOffset{m_columns - 1}; row < m_columns;
         ++row, --columnOffset)
    {
      if (m_table[row][columnOffset].m_playerFlag == playerMark)
      {
        m_table[row][columnOffset].reset();
      }
    }
  }
}

void
Board::_clearDiagonalWinLopsidedRow(const char playerMark)
{
  int columnOffSet{m_columns - m_rows};

  if (!m_diagonalReverseWin)
  {
    for (int columnStart{0}; columnStart <= columnOffSet; ++columnStart)
    {
      if (m_table[0][columnStart].m_playerFlag == playerMark)
      {
        for (int row{0}, column{columnStart}; row < m_rows; ++row, ++column)
        {
          if (m_table[row][column].m_playerFlag == playerMark)
          {
            m_table[row][column].reset();
          }
        }
      }
    }
  }
  else
  {
    for (int column{m_columns - 1}; column >= ((m_columns - 1) - columnOffSet);
         column--)
    {
      if (m_table[0][column].m_playerFlag == playerMark)
      {
        for (int row{0}; row < m_rows; row++)
        {
          if (m_table[row].at(static_cast<size_t>(column - row)).m_playerFlag ==
              playerMark)
          {
            m_table[row].at(static_cast<size_t>(column - row)).reset();
          }
        }
      }
    }
  }
}

void
Board::_clearDiagonalWinLopsidedColumn(const char playerMark)
{
  int rowOffset{m_rows - m_columns};

  if (!m_diagonalReverseWin)
  {
    for (int rowStart{0}; rowStart <= rowOffset; ++rowStart)
    {
      if (m_table[rowStart][0].m_playerFlag == playerMark)
      {
        for (int row{0}; row < (m_rows - rowOffset); ++row)
        {
          if (m_table.at(static_cast<size_t>(row + rowStart))[row]
                  .m_playerFlag == playerMark)
          {
            m_table[static_cast<size_t>(row + rowStart)][row].reset();
          }
        }
      }
    }
  }
  else
  {

    for (int rowStart{0}, lastColumn{m_columns - 1}; rowStart <= rowOffset;
         ++rowStart)
    {
      if (m_table[rowStart][lastColumn].m_playerFlag == playerMark)
      {
        for (int row{0}; row < (m_rows - rowOffset); row++)
        {
          if (m_table.at(static_cast<size_t>(row + rowStart))
                  .at(static_cast<size_t>(lastColumn - row))
                  .m_playerFlag == playerMark)
          {
            m_table[static_cast<size_t>(row + rowStart)]
                   [static_cast<size_t>(lastColumn - row)]
                       .reset();
          }
        }
      }
    }
  }
}

bool
Board::_multipleWinCases(const char playerMark) const
{
  int winCaseCount{};
  if (_isLateralWin(playerMark))
  {
    ++winCaseCount;
  }

  if (_isVerticalWin(playerMark))
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

  if (_isDiagonalWin(playerMark))
  {
    ++winCaseCount;
  }

  return (winCaseCount > 1);
}
#endif
