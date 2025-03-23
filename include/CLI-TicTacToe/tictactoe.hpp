#ifndef CLI_TICTACTOE_TICTACTOE_H
#define CLI_TICTACTOE_TICTACTOE_H

#include <CLI-TicTacToe/board.hpp>
#include <CLI-TicTacToe/player.hpp>

class TicTacToe
{
  struct MatchRecord
  {
    std::string_view m_winner{};
    std::string_view m_winCase{};

    int m_matchID{};
    int m_row{};

    int m_column{};
    int m_moves{};

    bool m_tieGame{};
  };

  using MatchRecords = std::vector<MatchRecord>;

public:
  TicTacToe();
  ~TicTacToe() = default;

  TicTacToe(const TicTacToe&) = delete;
  TicTacToe(const TicTacToe&&) = delete;

  TicTacToe&
  operator=(const TicTacToe&) = delete;

  TicTacToe&
  operator=(const TicTacToe&&) = delete;

private:
#ifdef BOARD_DEBUG
  struct DebugCommand
  {
    void
    reset()
    {
      m_commandString = " ";
      m_commandValue = 0;
    }
    std::string m_commandString{};
    int m_commandValue{};
  };

  DebugCommand m_debugCommand{};

  void
  _runCommand();
#endif // BOARD_DEBUG
  //setup Logic
  void
  _setupGame();

  void
  _setBoard();

  //Game Logic
  void
  _gameLoop();

  void
  _endGame();

  void
  _resetGame();

  //Move Logic
  void
  _getMove();

  void
  _move();

  bool
  _isLegalMove() const;

  bool
  _isValidPosition() const;

  //Win Logic
  bool
  _isWinningMove() const;

  bool
  _isTieGame() const;

  //Player Logic
  void
  _displayStats() const;

  void
  _nextPlayer();

  Player&
  _currentPlayer();

  //Util Methods
  void
  _displayBoard() const;

  void
  _displayBoardConfiguration() const;

  void
  _displayMatchRecords() const;

  static void
  _flushCin();

  void
  _checkBoardSize();

  void
  _createMatchRecord();

  void
  _quit() const;

  bool
  _stringToNumber(const std::string& number);

  //Member Vars
  Board m_board{};

  Player m_playerX{};
  Player m_playerO{};

  MatchRecords m_matchRecords{};

  int m_previousRow{};
  int m_previousColumn{};
  int m_tablePosition{};

  int m_totalInvalidMovesAllowed{};
  int m_tieGames{};

  char m_firstPlayer{};
  char m_currentPlayerMark{};

  bool m_hasWon{};
  bool m_tie{};
  bool m_isFirstGame{};
};
#endif // CLI_TICTACTOE_TICTACTOE_H
