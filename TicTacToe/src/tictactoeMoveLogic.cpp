#include "tictactoe.h"
#include <iostream>

#ifdef BOARD_DEBUG
#include <sstream>
#endif // BOARD_DEBUG

//Move Logic
void
TicTacToe::_getMove()
{
  std::cout << "|" << _currentPlayer().name()
            << ", please select a board number: ";
#ifndef BOARD_DEBUG
  std::cin >> m_tablePosition;
  _flushCin();
#else
  std::string command{};
  std::getline(std::cin, command);

  // Check to see if user enterd a number.
  // Otherwise, assume it's a debug command.
  // If not a debug command, do nothing as control will return to gameLoop.
  // (_runCommand --> _getMove() --> _gameLoop)
  // Which will check to see if m_tablePosition is valid.

  if (!_stringToNumber(command))
  {
    std::istringstream stream{command};

    stream >> m_debugCommand.m_commandString;
    stream >> m_debugCommand.m_commandValue;

    m_tablePosition = m_debugCommand.m_commandValue;
    _runCommand();
    m_debugCommand.reset();
  }
#endif // BOARD_DEBUG
}

void
TicTacToe::_move()
{
  _currentPlayer().addMove(m_tablePosition);
  m_board.coverBoardSlot(m_tablePosition, m_currentPlayerMark);
}

bool
TicTacToe::_isLegalMove() const
{
  if (_isValidPosition())
  {
    if (m_playerO.isOccupying(m_tablePosition) ||
        m_playerX.isOccupying(m_tablePosition))
    {
      return false;
    }

    return true;
  }

  return false;
}

bool
TicTacToe::_isValidPosition() const
{
  return m_tablePosition > 0 && m_tablePosition <= m_board.boardSize();
}

#ifdef BOARD_DEBUG
void
TicTacToe::_runCommand()
{
  if (m_debugCommand.m_commandString == "setL")
  {
    m_board.setLateralWin(m_debugCommand.m_commandValue, m_currentPlayerMark);
  }
  else if (m_debugCommand.m_commandString == "setV")
  {
    m_board.setVerticalWin(m_debugCommand.m_commandValue, m_currentPlayerMark);
  }
  else if (m_debugCommand.m_commandString == "setD")
  {
    if (m_board.isEvenBoard())
    {
      m_tablePosition = m_board.internalTable()[0][0].m_piecePosition;
    }

    m_board.setDiagonalWin(m_debugCommand.m_commandValue, m_currentPlayerMark);
  }
  else if (m_debugCommand.m_commandString == "setDr")
  {
    if (m_board.isEvenBoard())
    {
      m_tablePosition =
          m_board.internalTable()[0][static_cast<size_t>(m_board.columns() - 1)]
              .m_piecePosition;
    }

    m_board.setDiagonalWin(
        m_debugCommand.m_commandValue, m_currentPlayerMark, true);
  }
}
#endif // BOARD_DEBUG
