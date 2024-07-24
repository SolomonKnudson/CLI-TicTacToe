#include "tictactoe.hpp"
#include <iostream>
#include <limits>

//Display
void
TicTacToe::_displayBoard() const
{
  m_board.display();
}

void
TicTacToe::_displayBoardConfiguration() const
{
  std::cout << "|Match will be played on a " << m_previousRow << "x"
            << m_previousColumn << " Board!\n";
}

void
TicTacToe::_displayMatchRecords() const
{
  for (const auto& record : m_matchRecords)
  {
    std::cout << "\n|Match: " << record.m_matchID << '\n';
    std::cout << "|Played: on a " << record.m_row << "x" << record.m_column
              << " Board\n";
    if (!record.m_tieGame)
    {
      std::cout << "|Winner: " << record.m_winner << '\n';
      std::cout << "|Match won in: " << record.m_moves << " moves\n";
      std::cout << "|Win Case: " << record.m_winCase << '\n';
    }
    else
    {
      std::cout << "|No winner: match was a tie\n";
      std::cout << "|Total moves played: " << record.m_moves << '\n';
    }
  }
}

void
TicTacToe::_flushCin()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Sizing
void
TicTacToe::_checkBoardSize()
{
  if (m_previousRow < BoardTypes::standardRow &&
      m_previousColumn < BoardTypes::standardColumn)
  {
    std::cout << "|Invalid board size!\n";
    m_previousRow = BoardTypes::standardRow;
    m_previousColumn = BoardTypes::standardColumn;
  }
  else if (m_previousRow < BoardTypes::standardRow)
  {
    std::cout << "|Invalid row size!\n";
    m_previousRow = BoardTypes::standardRow;
  }
  else if (m_previousColumn < BoardTypes::standardColumn)
  {
    std::cout << "|Invalid column size!\n";
    m_previousColumn = BoardTypes::standardColumn;
  }

  if ((m_previousRow * m_previousColumn) > BoardTypes::maxSize)
  {
    std::cout << "|Exceeded max board size!\n";
    if (m_previousRow > BoardTypes::maxRow)
    {
      m_previousRow = BoardTypes::maxRow;
      if ((m_previousRow * m_previousColumn) > BoardTypes::maxSize)
      {
        m_previousColumn = BoardTypes::maxColumn;
      }
    }
    else if (m_previousColumn > BoardTypes::maxColumn)
    {
      m_previousColumn = BoardTypes::maxColumn;
    }
  }
}

//Match Records
void
TicTacToe::_createMatchRecord()
{
  static int numberOfGames{1};
  MatchRecord matchRecord{};

  matchRecord.m_matchID = numberOfGames++;
  matchRecord.m_row = m_previousRow;
  matchRecord.m_column = m_previousColumn;

  if (m_hasWon)
  {
    matchRecord.m_winner = _currentPlayer().name();
    matchRecord.m_moves = _currentPlayer().moves();
    matchRecord.m_winCase = m_board.winCase();
  }
  else
  {
    matchRecord.m_tieGame = true;
    //keep track of total moves played to display later if there's a tie
    matchRecord.m_moves = m_playerX.moves() + m_playerO.moves();
  }

  m_matchRecords.push_back(matchRecord);
}

#ifdef BOARD_DEBUG
#include <exception>
#include <string>
//STL Wrapper
//
//wrapper method for std::stoi, because stoi throws an exception if unable to convert input into a number.
//
bool
TicTacToe::_stringToNumber(const std::string& number)
{
  try
  {
    m_tablePosition = std::stoi(number);
    return true;
  }
  catch (const std::invalid_argument& isInFactNotANumber)
  {
    return false;
  }
}
#endif // BOARD_DEBUG
