#include "tictactoe.hpp"
#include <iostream>

//Constructors
TicTacToe::TicTacToe()
  : m_board{}

  , m_playerX{'X', "Player X"}
  , m_playerO{'O', "Player O"}

  , m_matchRecords{}

  , m_previousRow{}
  , m_previousColumn{}
  , m_tablePosition{}

  , m_totalInvalidMovesAllowed{3}
  , m_tieGames{}

  , m_firstPlayer{}
  , m_currentPlayerMark{}

  , m_hasWon{}
  , m_tie{}

  , m_isFirstGame{true}
{
  _setupGame();
}

//Setup Logic
void
TicTacToe::_setupGame()
{
  char userResponse{};
  std::cout << "|Press (S) for a standard " << BoardTypes::standardRow << "x"
            << BoardTypes::standardColumn
            << " board || (V) for a variable board{Row * Colum}{"
            << BoardTypes::standardRow << "x" << BoardTypes::standardColumn
            << " up to " << BoardTypes::maxRow << "x" << BoardTypes::maxColumn
            << ((!m_isFirstGame) ? "}  || (P) for previous board: " : "}: ");

  std::cin >> userResponse;
  _flushCin();

  switch (userResponse)
  {
    case 's':
    case 'S':
      m_previousRow = BoardTypes::standardRow;
      m_previousColumn = BoardTypes::standardColumn;

      _displayBoardConfiguration();
      _setBoard();
      break;
    case 'v':
    case 'V':
      std::cout << "|Enter # of rows: ";
      std::cin >> m_previousRow;
      _flushCin();

      std::cout << "|Enter # of columns: ";
      std::cin >> m_previousColumn;
      _flushCin();

      _checkBoardSize();
      _displayBoardConfiguration();
      _setBoard();
      break;
    case 'p':
    case 'P':
      if (!m_isFirstGame)
      {
        _displayBoardConfiguration();
        _setBoard();
        break;
      }
      [[fallthrough]];
    default:
      std::cout << "|Not one of the options listed!\n";

      m_previousRow = BoardTypes::standardRow;
      m_previousColumn = BoardTypes::standardColumn;

      _displayBoardConfiguration();
      _setBoard();
      break;
  }
  if (m_isFirstGame)
  {
    m_isFirstGame = false;
    std::cout << "|Who goes first!?! (X) || (O): ";
    std::cin >> userResponse;
    _flushCin();
    switch (userResponse)
    {
      case 'o':
      case 'O':
        m_firstPlayer = m_playerO.mark();
        m_currentPlayerMark = m_firstPlayer;
        break;
      case 'x':
      case 'X':
        m_firstPlayer = m_playerX.mark();
        m_currentPlayerMark = m_firstPlayer;
        break;
      default:
        std::cout << "|No idea who that is!\n|Player X, you start!\n";

        m_firstPlayer = m_playerX.mark();
        m_currentPlayerMark = m_firstPlayer;
        break;
    }
    _gameLoop();
  }
}

void
TicTacToe::_setBoard()
{
  m_board.setBoard(m_previousRow, m_previousColumn);
}

//Win Logic
bool
TicTacToe::_isWinningMove() const
{
  return m_board.isWinningMove(m_currentPlayerMark);
}

bool
TicTacToe::_isTieGame() const
{
  return m_board.isTie();
}

//Player Logic
void
TicTacToe::_displayStats() const
{
  std::cout << "\n         Win || Loss\n";
  std::cout << "----------------------\n";

  std::cout << m_playerX.name() << ": " << m_playerX.wins() << " || "
            << m_playerO.wins() << '\n';

  std::cout << "----------------------\n";

  std::cout << m_playerO.name() << ": " << m_playerO.wins() << " || "
            << m_playerX.wins() << '\n';

  std::cout << "----------------------\n";
  std::cout << "|Ties    : " << m_tieGames << '\n';
  std::cout << "----------------------\n";
}

void
TicTacToe::_nextPlayer()
{
  (m_currentPlayerMark == m_playerX.mark())
      ? m_currentPlayerMark = m_playerO.mark()
      : m_currentPlayerMark = m_playerX.mark();
}

Player&
TicTacToe::_currentPlayer()
{
  return ((m_currentPlayerMark == m_playerX.mark()) ? m_playerX : m_playerO);
}
