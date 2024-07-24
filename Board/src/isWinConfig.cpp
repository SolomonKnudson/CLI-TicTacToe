#include "board.hpp"
using namespace BoardTypes;

//Win Logic
bool
Board::isWinningMove(const char playerMark) const
{
  if (_isLateralWin(playerMark))
  {
    m_winCase = WinCase::Lateral;
    return true;
  }
  else if (_isVerticalWin(playerMark))
  {
    m_winCase = WinCase::Vertical;
    return true;
  }
  else if (_isDiagonalWin(playerMark))
  {
    m_winCase = WinCase::Diagonal;
    return true;
  }

  return false;
}

//Util methods for isWinningMove
bool
Board::_isLateralWin(const char playerMark) const
{
  int inARow{};
  for (const auto& row : m_table)
  {
    for (const auto& column : row)
    {
      if (column.m_playerFlag == playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_columns)
    {
      return true;
    }
    inARow = 0;
  }

  return false;
}

bool
Board::_isVerticalWin(const char playerMark) const
{
  int inARow{};
  for (int column{0}; column < m_columns; ++column)
  {
    for (int row{0}; row < m_rows; ++row)
    {
      if (m_table[row][column].m_playerFlag == playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_rows)
    {
      return true;
    }
    inARow = 0;
  }

  return false;
}

bool
Board::_isDiagonalWin(const char playerMark) const
{
  if (m_evenBoard)
  {
    return _isDiagonalWinEvenBoard(playerMark);
  }
  else if (m_rows < m_columns)
  {
    return _isDiagonalWinLopsidedRow(playerMark);
  }
  else if (m_columns < m_rows)
  {
    return _isDiagonalWinLopsidedColumn(playerMark);
  }

  return false;
}

//Util methods for isDiaWin
bool
Board::_isDiagonalWinEvenBoard(const char playerMark) const
{
  int inARow{};
  for (int row{0}, column{0}; row < m_rows; ++row, ++column)
  {
    if (m_table[row][column].m_playerFlag == playerMark)
    {
      inARow++;
      continue;
    }
    break;
  }

  if (inARow == m_rows)
  {
    return true;
  }
  inARow = 0;

  //Reverse case
  for (int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
  {
    if (m_table[row].at(static_cast<size_t>(columnOffSet - row)).m_playerFlag ==
        playerMark)
    {
      inARow++;
      continue;
    }
    break;
  }

  return (inARow == m_rows);
}

/*
    *NOTE: if rows < columns, columns - rows = only diagonal cases(Column Based)
    *ex. 4x8: Diagonal cases: column: 0, 1, 2, 3, 4 index based!
    *10x11: Diagonal cases: column: 0, 1
    *
*/
bool
Board::_isDiagonalWinLopsidedRow(const char playerMark) const
{
  int inARow{};
  int columnOffset{m_columns - m_rows};

  for (int column{0}; column <= columnOffset; ++column)
  {
    for (int row{0}; row < m_rows; ++row)
    {
      if (m_table[row].at(static_cast<size_t>(column + row)).m_playerFlag ==
          playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_rows)
    {
      return true;
    }
    inARow = 0;
  }

  inARow = 0;

  //Reverse case
  for (int column{m_columns - 1}; column >= ((m_columns - 1) - columnOffset);
       --column)
  {
    for (int row{0}; row < m_rows; row++)
    {
      if (m_table[row].at(static_cast<size_t>(column - row)).m_playerFlag ==
          playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_rows)
    {
      return true;
    }
    inARow = 0;
  }

  return false;
}

/*
    *NOTE: if columns < rows, rows -  columns = only diagonal cases(Row Based);
    *must account for a 'lower' row diagonal win
    *ex. 8x4: Diagonal cases: row: 0, 1, 2, 3, 4 index based!
    *15x11: Diagonal cases: row: 0, 1, 2, 3, 4
*/
bool
Board::_isDiagonalWinLopsidedColumn(const char playerMark) const
{
  int inARow{};
  int rowOffset{m_rows - m_columns};
  for (int rowStart{0}; rowStart <= rowOffset; ++rowStart)
  {

    for (int row{0}; row < (m_rows - rowOffset); ++row)
    {
      if (m_table.at(static_cast<size_t>(rowStart + row))[row].m_playerFlag ==
          playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_columns)
    {
      return true;
    }
    inARow = 0;
  }

  inARow = 0;

  //Reverse case
  for (int rowStart{0}; rowStart <= rowOffset; ++rowStart)
  {
    for (int row{0}, column{m_columns - 1}; row < (m_rows - rowOffset); row++)
    {
      if (m_table.at(static_cast<size_t>(row + rowStart))
              .at(static_cast<size_t>(column - row))
              .m_playerFlag == playerMark)
      {
        inARow++;
        continue;
      }
      break;
    }

    if (inARow == m_columns)
    {
      return true;
    }
    inARow = 0;
  }

  return false;
}

bool
Board::isTie() const
{
  int totalPlayerMarks{};
  for (const auto& row : m_table)
  {
    for (const auto& column : row)
    {
      if (column.m_playerIsOccupying)
      {
        totalPlayerMarks++;
        continue;
      }
      return false;
    }
  }

  return (totalPlayerMarks == m_boardSize);
}
