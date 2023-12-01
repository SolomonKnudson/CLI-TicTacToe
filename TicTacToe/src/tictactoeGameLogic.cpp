#include "tictactoe.h"

//Game Logic
void TicTacToe::_gameLoop()
{
    while (!m_hasWon && !m_tie)
    {
        _displayBoard();
        _getMove();
        if (!_isLegalMove())
        {
            _currentPlayer().addInvalidMove();
            while (_currentPlayer().invalidMoves()
                <= m_totalInvalidMovesAllowed)
            {
                std::cout << "|Watch it, " << _currentPlayer().name()
                    << ", that's an invalid table position,"
                    << " you have " << m_totalInvalidMovesAllowed
                    - _currentPlayer().invalidMoves()
                    << " left!\n";
                _getMove();
                if (_isLegalMove())
                {
                    break;
                }
                _currentPlayer().addInvalidMove();
            }
            if (_currentPlayer().invalidMoves()
                    > m_totalInvalidMovesAllowed)
            {
                std::cout << "|" << _currentPlayer().name()
                    << ", you have exceeded the max # of "
                    << "invalid moves allowed!\n|You will now forfeit "
                    << "your current turn and future turns upon "
                    << "detection of an invalid move!\n";
                _nextPlayer();
                continue;
            }
        }
        _move();
//if win was set by a debug command, the win checks will not be called, as debug commands do not add to player moves. if in debug, skip check.
#ifndef BOARD_DEBUG
        //isWinningMove does a lot of looping. Only call once current player has
        //made the minimum number of moves to have a win
        if (_currentPlayer().moves() >=
            ((m_previousRow < m_previousColumn) ? m_previousRow
                : m_previousColumn))
        {
            if (_isWinningMove())
            {
                m_hasWon = true;
                break;
            }
            else if (_isTieGame())
            {
                m_tie = true;
                break;
            }
        }
#else
        if (m_endGameCalled)
        {
            break;
        }
        if (_isWinningMove())
        {
            m_hasWon = true;
            break;
        }
        else if (_isTieGame())
        {
            m_tie = true;
            break;
        }
#endif

        _nextPlayer();
    }
#ifdef BOARD_DEBUG
    if (m_endGameCalled)
    {
        m_endGameCalled = false;
    }
    else
    {
        _displayBoard();
    }
    _createMatchRecord();
    _endGame();
#else // def BOARD_DEBUG
    _displayBoard();
    _createMatchRecord();
    _endGame();
#endif
}

void TicTacToe::_endGame()
{
    if (m_hasWon)
    {
        std::cout << "|Tic-Tac-Toe!\n|Congrats, "
            << _currentPlayer().name() << "! You Win!\n";
        std::cout << "|You beat " << ((m_currentPlayerMark == m_playerX.mark())
            ? m_playerO.name() : m_playerX.name())
            << " in " << _currentPlayer().moves()
            << " moves!";
        _currentPlayer().addWin();
    }
    else if (m_tie)
    {
        std::cout << "|Tie game! Well played, X, O!\n";
        m_tieGames++;
    }
    _displayStats();
    char userResponse{};
    std::cout << "|(P) to play again || (Q) to quit: ";
    std::cin >> userResponse;
    _flushCin();
    switch (userResponse)
    {
    case 'P':
    case 'p':
        _resetGame();
        break;
    case 'q':
    case 'Q':
        _quit();
        break;
    default:
        std::cout << "|Gonna assume you want to play again!\n";
        _resetGame();
        break;
    }
}

void TicTacToe::_resetGame()
{
    _setupGame();
    if (m_hasWon)
    {
        m_hasWon = false;
        m_firstPlayer = m_currentPlayerMark;
        std::cout << "|Winner starts!\n";
    }
    else if (m_tie)
    {
        m_tie = false;
        m_firstPlayer = ((m_firstPlayer == m_playerX.mark()) ? m_playerO.mark()
            : m_playerX.mark());
        m_currentPlayerMark = m_firstPlayer;
        std::cout << "|Last game was a tie; "
            << _currentPlayer().name() << " will start!\n";

    }
    m_playerX.clearMoves();
    m_playerX.resetInvalidMoves();

    m_playerO.clearMoves();
    m_playerO.resetInvalidMoves();

    m_tablePosition = 0;
    _gameLoop();
}


void TicTacToe::_quit() const
{
    _displayStats();
    _displayMatchRecords();
    if (m_playerX.wins() != m_playerO.wins())
    {
        std::cout << "\n|Congrats, " << ((m_playerX.wins() > m_playerO.wins())
            ? m_playerX.name() : m_playerO.name())
            << "!\n|You had the most wins with: "
            << ((m_playerX.wins() > m_playerO.wins()) ?
                m_playerX.wins() : m_playerO.wins()) << "!\n";
    }
    else
    {
        std::cout << "\n|Tie Game! No Winner.\n";
    }

    std::cout << "\n|Thank you for playing! Have a lovely rest of your "
        << "day/night!\n";
    std::cout << "|Thank you, CJ, for challenging me to create "
        << "Tic-Tac-Toe,\n|and for helping to test the game logic.";
    std::cout << "\n|GoodBye!\n\n";
}