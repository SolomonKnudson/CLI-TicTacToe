#include "tictactoe.h"

//Constructors
TicTacToe::TicTacToe()
    : m_board{}

    , m_playerX{-1, "Player X"}
    , m_playerO{-2, "Player O"}

    , m_matchRecords{}

    , m_previousRow{}
    , m_previousColumn{}
    , m_tablePosition{}

    , m_firstPlayer{}
    , m_currentPlayerMark{}
    , m_totalInvalidMovesAllowed{3}

    , m_tieGames{}
    , m_hasWon{}
    , m_tie{}

    , m_isFirstGame{true}
{
    _setupGame();
}


//Setup Logic
void TicTacToe::_setupGame()
{
    char userResponse{};
    std::cout << "|Press (S) for a standard " << Board::standardRow << "x"
              << Board::standardColumn
              << " board || (V) for a variable board{Row * Colum}{"
              <<  Board::standardRow << "x" << Board::standardColumn
              <<" up to " << Board::maxRow << "x" << Board::maxColumn
              << ((!m_isFirstGame) ? "}  || (P) for previous board: "
                                  :"}: ");
    std::cin >> userResponse;
    _flushCin();
    switch(userResponse)
    {
        case 's':
        case 'S':
            m_previousRow = Board::standardRow;
            m_previousColumn = Board::standardColumn;
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
            if(!m_isFirstGame)
            {
                _displayBoardConfiguration();
                _setBoard();
                break;
            }
       [[fallthrough]];
        default:
            std::cout << "|Not one of the options listed!\n";
            m_previousRow = Board::standardRow;
            m_previousColumn = Board::standardColumn;
            _displayBoardConfiguration();
            _setBoard();
            break;
    }
    if(m_isFirstGame)
    {
        m_isFirstGame = false;
        std::cout << "|Who goes first!?! (X) || (O): ";
        std::cin >> userResponse;
        _flushCin();
        switch(userResponse)
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

void TicTacToe::_setBoard()
{
    m_board.setBoard(m_previousRow, m_previousColumn);
}

//Game Logic
void TicTacToe::_gameLoop()
{
    while(!m_hasWon && !m_tie)
    {
        _displayBoard();
        _getMove();
        if(!_isLegalMove())
        {
            _currentPlayer().addInvalidMove();
            while(_currentPlayer().invalidMoves()
                  <= m_totalInvalidMovesAllowed)
            {
                std::cout << "|Watch it, " << _currentPlayer().name()
                          << " that's an invalid table position,"
                          << " you have " << m_totalInvalidMovesAllowed
                             - _currentPlayer().invalidMoves()
                          << " left!\n";
                _getMove();
                if(_isLegalMove())
                {
                    break;
                }
                _currentPlayer().addInvalidMove();
            }
            if(_currentPlayer().invalidMoves()
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
        //isWinningMove does a lot of looping. Only call once current player has
        //made the minimum number of moves to have a win
        if(_currentPlayer().moves() >=
                ((m_previousRow < m_previousColumn) ? m_previousRow
                 : m_previousColumn))
        {
            if(_isWinningMove())
            {
                m_hasWon = true;
                break;
            }
            else if(_isTieGame())
            {
                m_tie = true;
                break;
            }
        }
        _nextPlayer();
    }
   _displayBoard();
   _createMatchRecord();
   _endGame();
}

void TicTacToe::_endGame()
{
    if(m_hasWon)
    {
        std::cout << "|Tic-Tac-Toe!\n|Congrats, "
                  << _currentPlayer().name() << "! You Win!\n";
        std::cout << "|You beat " << ((m_currentPlayerMark == m_playerX.mark())
                                      ? m_playerO.name() : m_playerX.name())
                                  << " in " << _currentPlayer().moves()
                                  << " moves!";
        _currentPlayer().addWin();
    }
    else if(m_tie)
    {
        std::cout << "|Tie game! Well played, X, O!\n";
        m_tieGames++;
    }
    _displayStats();
    char userResponse{};
    std::cout << "|(P) to play again || (Q) to quit: ";
    std::cin >> userResponse;
    _flushCin();
    switch(userResponse)
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
    if(m_hasWon)
    {
        m_hasWon = false;
        m_firstPlayer = m_currentPlayerMark;
        std::cout << "|Winner starts!\n";
    }
    else if(m_tie)
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


//Move Logic
void TicTacToe::_getMove()
{
    std::cout << "|" << _currentPlayer().name()
              << ", please select a board number: ";
    
#ifndef BOARD_DEBUG
    std::cin >> m_tablePosition;
    _flushCin();
#else
    std::string command{};
    std::getline(std::cin, command);
    //If stoi doesn't blow up, user entered a number. Otherwise, check to see if its a debug command
    //If not a debug command, do nothing as control will return to gameLoop
    //(_runCommand --> _getMove() --> _gameLoop)
    // Which will check to see if the m_tablePosition is valid
    try
    {
        m_tablePosition = std::stoi(command);
    }
    catch (const std::exception& error)
    {
        m_tablePosition = 0;
        std::istringstream stream{command};
        stream >> m_debugCommand.m_commandString;
        stream >> m_debugCommand.m_commandValue;
        _runCommand();
    }
#endif // BOARD_DEBUG
}

#ifdef BOARD_DEBUG
void TicTacToe::_runCommand()
{
    bool gameEndingCommand{};
    if (m_debugCommand.m_commandString == "setL")
    {
        gameEndingCommand = true;
        m_board.setLateralWin(m_debugCommand.m_commandValue, m_currentPlayerMark);
    }
    if (gameEndingCommand)
    {
        _displayBoard();
        _endGame();
    }
}
#endif // BOARD_DEBUG




void TicTacToe::_move()
{
    _currentPlayer().addMove(m_tablePosition);
    m_board.coverBoardSlot(m_tablePosition, m_currentPlayerMark);
}

bool TicTacToe::_isLegalMove() const
{
    if(_isValidPosition())
    {
        if(m_playerO.isOccupying(m_tablePosition)
                || m_playerX.isOccupying(m_tablePosition))
        {
            return false;
        }
        return true;
    }
    return false;
}

//Win Logic
bool TicTacToe::_isWinningMove() const
{
    return m_board.isWinningMove(m_currentPlayerMark);
}

bool TicTacToe::_isTieGame() const
{
    return m_board.isTie(m_playerX.mark(), m_playerO.mark());
}

//Player Logic
void TicTacToe::_displayStats() const
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

void TicTacToe::_nextPlayer()
{
    (m_currentPlayerMark == m_playerX.mark())
            ? m_currentPlayerMark = m_playerO.mark()
            : m_currentPlayerMark = m_playerX.mark();
}

Player& TicTacToe::_currentPlayer()
{
    return ((m_currentPlayerMark == m_playerX.mark()) ? m_playerX : m_playerO);
}

//Util
void TicTacToe::_flushCin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TicTacToe::_checkBoardSize()
{
    if(m_previousRow < Board::standardRow
            && m_previousColumn < Board::standardColumn)
    {
        std::cout << "|Invalid board size!\n";
        m_previousRow = Board::standardRow;
        m_previousColumn = Board::standardColumn;
    }
    else if(m_previousRow < Board::standardRow)
    {
        std::cout << "|Invalid row size!\n";
        m_previousRow = Board::standardRow;
    }
    else if(m_previousColumn < Board::standardColumn)
    {
        std::cout << "|Invalid column size!\n";
        m_previousColumn = Board::standardColumn;
    }

    if((m_previousRow * m_previousColumn) > Board::maxSize)
    {
        std::cout << "|Exceeded max board size!\n";
        if(m_previousRow > Board::maxRow)
        {
            m_previousRow = Board::maxRow;
            if((m_previousRow * m_previousColumn) > Board::maxSize)
            {
                m_previousColumn = Board::maxColumn;
            }
        }
        else if(m_previousColumn > Board::maxColumn)
        {
            m_previousColumn = Board::maxColumn;
        }
    }
}

void TicTacToe::_displayBoard() const
{
    m_board.display(m_playerX.mark(), m_playerO.mark());
}

void TicTacToe::_displayBoardConfiguration() const
{
    std::cout << "|Match will be played on a "
              << m_previousRow << "x" << m_previousColumn
              << " Board!\n";
}

void TicTacToe::_createMatchRecord()
{
    static int numberOfGames{1};
    MatchRecord matchRecord{};
    matchRecord.m_matchID = numberOfGames++;
    matchRecord.m_row = m_previousRow;
    matchRecord.m_column = m_previousColumn;
    if(m_hasWon)
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

void TicTacToe::_displayMatchRecords() const
{
    for(const auto& record : m_matchRecords)
    {
        std::cout << "\n|Match: " << record.m_matchID << '\n';
        std::cout << "|Played: on a " << record.m_row << "x" << record.m_column
                  << " Board\n";
        if(!record.m_tieGame)
        {
            std::cout << "|Winner: " << record.m_winner << '\n';
            std::cout << "|Match won in: " << record.m_moves
                      << " moves\n";
            std::cout << "|Win Case: " << record.m_winCase << '\n';
        }
        else
        {
            std::cout << "|No winner: match was a tie\n";
            std::cout << "|Total moves played: " << record.m_moves << '\n';
        }
    }
}

bool TicTacToe::_isValidPosition() const
{
    return m_tablePosition > 0 && m_tablePosition <= m_board.boardSize();
}

void TicTacToe::_quit() const
{
    _displayStats();
    _displayMatchRecords();
    if(m_playerX.wins() != m_playerO.wins())
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
    std::exit(0);
}