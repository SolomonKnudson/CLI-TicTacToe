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
    this -> setupGame();
}
//END CONSTRUCTORS

//Private Methods
//Setup Logic
void TicTacToe::setupGame()
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
    this -> flushCin();
    switch(userResponse)
    {
        case 's':
        case 'S':
            m_previousRow = Board::standardRow;
            m_previousColumn = Board::standardColumn;
            this -> displayBoardConfiguration();
            this -> setBoard();
            break;
        case 'v':
        case 'V':
            std::cout << "|Enter # of rows: ";
            std::cin >> m_previousRow;
            this -> flushCin();
            std::cout << "|Enter # of columns: ";
            std::cin >> m_previousColumn;
            this -> flushCin();
            this -> checkBoardSize();
            this -> displayBoardConfiguration();
            this -> setBoard();
            break;
        case 'p':
        case 'P':
            if(!m_isFirstGame)
            {
                this -> displayBoardConfiguration();
                this -> setBoard();
                break;
            }
        default:
            std::cout << "|Not one of the options listed!\n";
            m_previousRow = Board::standardRow;
            m_previousColumn = Board::standardColumn;
            this -> displayBoardConfiguration();
            this -> setBoard();
            break;
    }
    if(m_isFirstGame)
    {
        m_isFirstGame = false;
        std::cout << "|Who goes first!?! (X) || (O): ";
        std::cin >> userResponse;
        this -> flushCin();
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
        this -> gameLoop();
    }
}

void TicTacToe::setBoard()
{
    if(!m_board.isEmpty())
    {
        m_board.resetBoard();
    }
    m_board.setBoard(m_previousRow, m_previousColumn);
}

//Board Logic
void TicTacToe::displayBoard() const
{
    m_board.display(m_playerX.mark(), m_playerO.mark());
}

//Game Logic
void TicTacToe::gameLoop()
{
    while(!m_hasWon && !m_tie)
    {
        this -> displayBoard();
        this -> getMove();
        if(!this -> isLegalMove())
        {
            this -> currentPlayer().addInValidMove();
            while(this -> currentPlayer().inValidMoves()
                  <= m_totalInvalidMovesAllowed)
            {
                std::cout << "|Watch it, " << this -> currentPlayer().name()
                          << " that's an invalid table position,"
                          << " you have " << m_totalInvalidMovesAllowed
                             - this -> currentPlayer().inValidMoves()
                          << " left!\n";
                this -> getMove();
                if(this -> isLegalMove())
                {
                    break;
                }
                this -> currentPlayer().addInValidMove();
            }
            if(this -> currentPlayer().inValidMoves()
                    > m_totalInvalidMovesAllowed)
            {
                std::cout << "|" << this -> currentPlayer().name()
                          << ", you have exceeded the max # of "
                          << "invalid moves allowed!\n|You will now forfit "
                          << "your current turn and future turns upon "
                          << "detection of an invalid move!\n";
                this -> nextPlayer();
                continue;
            }
        }
        this -> move();
        if(this -> isWinningMove())
        {
            m_hasWon = true;
        }
        else if(this -> isTieGame())
        {
            m_tie = true;
        }
        else
        {
            this -> nextPlayer();
        }
    }
   this -> displayBoard();
   this -> createMatchRecord();
   this -> endGame();
}

void TicTacToe::endGame()
{
    if(m_hasWon)
    {
        std::cout << "|Tic-Tac-Toe!\n|Congrats, "
                  << this -> currentPlayer().name() << "! You Win!\n";
        if(m_currentPlayerMark == m_playerX.mark())
        {
            std::cout << "|You beat " << m_playerO.name() << " in "
                      << m_playerX.moves() << " moves!\n";
            m_playerX.addWin();
        }
        else
        {
            std::cout << "|You beat " << m_playerX.name() << " in "
                      << m_playerO.moves() << " moves!\n";
            m_playerO.addWin();
        }
    }
    else if(m_tie)
    {
        std::cout << "|Tie game! Well played, X, O!\n";
        m_tieGames++;
    }
    this -> displayStats();
    char userResponse{};
    std::cout << "|(P) to play again || (Q) to quit: ";
    std::cin >> userResponse;
    this -> flushCin();
    switch(userResponse)
    {
        case 'P':
        case 'p':
            this -> resetGame();
            break;
        case 'q':
        case 'Q':
            this -> quit();
            break;
        default:
            std::cout << "|Gonna assume you want to play again!\n";
            this -> resetGame();
            break;
    }
}

void TicTacToe::resetGame()
{
    this -> setupGame();
    if(m_hasWon)
    {
        m_hasWon = false;
        m_firstPlayer = m_currentPlayerMark;
        std::cout << "|Winner starts!\n";
    }
    else if(m_tie)
    {
        m_tie = false;
        if(m_firstPlayer == m_playerX.mark())
        {
            m_firstPlayer = m_playerO.mark();
            m_currentPlayerMark = m_firstPlayer;
        }
        else
        {
            m_firstPlayer = m_playerX.mark();
            m_currentPlayerMark = m_firstPlayer;
        }
        std::cout << "|Last game was a tie; "
                  << this -> currentPlayer().name() << " will start!\n";

    }
    m_playerX.clearMoves();
    m_playerX.resetInValidMoves();

    m_playerO.clearMoves();
    m_playerO.resetInValidMoves();

    m_tablePosition = 0;
    this -> gameLoop();
}

//Move Logic
void TicTacToe::getMove()
{
    std::cout << "|" << this -> currentPlayer().name()
              << ", please select a board number: ";
    std::cin >> m_tablePosition;
    flushCin();
}

void TicTacToe::move()
{
    (m_currentPlayerMark == m_playerX.mark())
            ? m_playerX.addMove(m_tablePosition)
            : m_playerO.addMove(m_tablePosition);
    m_board.coverBoardSlot(m_tablePosition, m_currentPlayerMark);
}

bool TicTacToe::isLegalMove() const
{
    if(this -> isValidPosition())
    {
        if(m_playerO.inMoves(m_tablePosition)
                || m_playerX.inMoves(m_tablePosition))
        {
            return false;
        }
        return true;
    }
    return false;
}

//Win Logic
bool TicTacToe::isWinningMove() const
{
    return m_board.isWinningMove(m_currentPlayerMark);
}

bool TicTacToe::isTieGame() const
{
    return m_board.isTie(m_playerX.mark(), m_playerO.mark());
}

//Player Logic
void TicTacToe::displayStats() const
{
    std::cout << "\n         Win || Loss\n";
    std::cout << "----------------------\n";
    if(Board::isSingleDigit(m_playerX.wins()))
    {
        std::cout << "|Player X: " << m_playerX.wins() << "   || "
                  << m_playerO.wins() <<'\n';
    }
    else if(Board::isDoubleDigit(m_playerX.wins()))
    {
        std::cout << "|Player X: " << m_playerX.wins() << "  || "
                  << m_playerO.wins() <<'\n';
    }
    else if(Board::isTripleDigit(m_playerX.wins()))
    {
        std::cout << "|Player X: " << m_playerX.wins() << " || "
                  << m_playerO.wins() <<'\n';
    }
    std::cout << "----------------------\n";
    if(Board::isSingleDigit(m_playerO.wins()))
    {
        std::cout << "|Player O: " << m_playerO.wins() << "   || "
                  << m_playerX.wins() <<'\n';
    }
    else if(Board::isDoubleDigit(m_playerO.wins()))
    {
        std::cout << "|Player O: " << m_playerO.wins() << "  || "
                  << m_playerX.wins() <<'\n';
    }
    else if(Board::isTripleDigit(m_playerO.wins()))
    {
        std::cout << "|Player O: " << m_playerO.wins() << " || "
                  << m_playerX.wins() <<'\n';
    }
    std::cout << "----------------------\n";
    std::cout << "|Ties    : " << m_tieGames << '\n';
    std::cout << "----------------------\n";
}

void TicTacToe::nextPlayer()
{
    (m_currentPlayerMark == m_playerX.mark())
            ? m_currentPlayerMark = m_playerO.mark()
            : m_currentPlayerMark = m_playerX.mark();
}

Player& TicTacToe::currentPlayer()
{
    return ((m_currentPlayerMark == m_playerX.mark()) ? m_playerX : m_playerO);
}

//Util
void TicTacToe::flushCin() const
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TicTacToe::checkBoardSize()
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

void TicTacToe::displayBoardConfiguration() const
{
    std::cout << "|Match will be played on a "
              << m_previousRow << "x" << m_previousColumn
              << " Board!\n";
}
void TicTacToe::displayMatchRecords() const
{
    for(const auto& record : m_matchRecords)
    {
        std::cout << "\n|Match: " << record.m_matchID << '\n';
        std::cout << "|Played on a " << record.m_row << "x" << record.m_column
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

void TicTacToe::createMatchRecord()
{
    static int numberOfGames{1};
    MatchRecord matchRecord{};
    matchRecord.m_matchID = numberOfGames++;
    matchRecord.m_row = m_previousRow;
    matchRecord.m_column = m_previousColumn;
    if(m_hasWon)
    {
        matchRecord.m_winner = this -> currentPlayer().name();
        matchRecord.m_moves = this -> currentPlayer().moves();
        matchRecord.m_winCase = m_board.winCase();
    }
    else
    {
        matchRecord.m_tieGame = true;
        //keep track of total moves played to diplay later if theres a tie
        matchRecord.m_moves = m_playerX.moves() + m_playerO.moves();
    }
    m_matchRecords.push_back(matchRecord);
}

bool TicTacToe::isValidPosition() const
{
    return m_tablePosition > 0 && m_tablePosition <= m_board.boardSize();
}

void TicTacToe::quit() const
{
    this -> displayStats();
    this -> displayMatchRecords();
    if(m_playerX.wins() > m_playerO.wins())
    {
        std::cout << "\n|Congrats, " << m_playerX.name()
                  << "!\n|You had the most wins with: "
                  << m_playerX.wins() << "!\n";
    }
    else if(m_playerO.wins() > m_playerX.wins())
    {
        std::cout << "\n|Congrats, " << m_playerO.name()
                  << "!\n|You had the most wins with: "
                  << m_playerO.wins() << "!\n";
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
//END PRIVATE METHODS
