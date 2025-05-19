#include <CLI-TicTacToe/board.hpp>
#include <iostream>
#include <string_view>
using namespace BoardTypes;

//Util Logic
WinCase
Board::winCase() const
{
  return m_winCase;
}

std::string_view
Board::winCaseToString() const
{
  switch (m_winCase)
  {
    case WinCase::Lateral:
      return "Lateral";

    case WinCase::Vertical:
      return "Vertical";

    case WinCase::Diagonal:
      return "Diagonal";

    case WinCase::NoWinCase:
      break;
  }

  return "NoWinCase";
}

void
Board::resetBoard()
{
  m_table.clear();
  m_rows = 0;
  m_columns = 0;
  m_boardSize = 0;

  if (m_evenBoard)
  {
    m_evenBoard = false;
  }

  m_winCase = WinCase::NoWinCase;
}

//Methods to help with display formatting
//Positive ints only!
bool
Board::_isSingleDigit(const int column)
{
  return column < 10;
}

bool
Board::_isDoubleDigit(const int column)
{
  return column >= 10 && column < 100;
}

bool
Board::_isTripleDigit(const int column)
{
  return column >= 100 && column < 1000;
}

void
Board::_dashLine() const
{
  for (int dashLine{0}; dashLine < m_columns; dashLine++)
  {
    if (dashLine == 0)
    {
      std::cout << "|----|";
    }
    else
    {
      std::cout << "----|";
    }
  }

  std::cout << '\n';
}

bool
Board::isEmpty() const
{
  return m_table.empty();
}

int
Board::rows() const
{
  return m_rows;
}

int
Board::columns() const
{
  return m_columns;
}

int
Board::boardSize() const
{
  return m_boardSize;
}

bool
Board::isEvenBoard() const
{
  return m_evenBoard;
}

const Table&
Board::cInternalTable() const
{
  return m_table;
}

Table&
Board::internalTable()
{
  return m_table;
}

#ifdef BOARD_DEBUG
void
Board::setWinCase(const WinCase winCase)
{
  m_winCase = winCase;
}
#endif
