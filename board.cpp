#include "board.h"

//Constructors
Board::Board(const int row, const int column)
    : m_table{}
    , m_winCase{}
    , m_rows{}
    , m_columns{}
    , m_boardSize{}
    , m_evenBoard{}
{
    if(row >= 3 && column >= 3)
    {
        this -> setBoard(row, column);
    }
}
//END CONSTRUCTORS

//Public Methods

//Table Logic
void Board::display(const int playerX, const int playerO) const
{
/*
    *  What board is supposed to look like
    *  |---|---|---|
    *  |1  |2  |3  |
    *  |---|---|---|
    *  |14 |15 |16 |
    *  |---|---|---|
    *  |700|800|900|
    *  |---|---|---|
*/
    this -> dashLine();
    for(const auto& row : m_table)
    {
        std::cout << "|";
        for(const auto& column : row)
        {
            if(column == playerX)
            {
                std::cout << " X  |";
//                std::cout << " " << column << " |";
            }
            else if(column == playerO)
            {
                std::cout << " O  |";
//                std::cout << " " << column << " |";
            }
            else
            {//  |1   |2   |3   |
                if(this -> isSingleDigit(column))
                {
                    std::cout << " " << column << "  |";
                }//  |14  |15  |16  |
                else if(this -> isDoubleDigit(column))
                {
                    std::cout << " " << column << " |";
                }//|700 |800 |900 |
                else if(this -> isTripleDigit(column))
                {
                    std::cout << " " << column << "|";
                }//1000|2000|3000
                else
                {
                    std::cout << column << "|";
                }
            }
        }
        std::cout << '\n';
        this -> dashLine();
    }
}

int Board::rows() const
{
    return m_rows;
}

int Board::columns() const
{
    return m_columns;
}

int Board::boardSize() const
{
    return m_boardSize;
}

void Board::setBoard(int rows, int columns)
{
    m_rows = rows;
    m_columns = columns;
    m_boardSize = m_rows * m_columns;

    if(m_rows == m_columns)
    {
        m_evenBoard = true;
    }

    for(int row{0}; row < m_rows; row++)
    {
        m_table.push_back(std::vector<int>{});
    }

    int column{1};

    for(auto& row : m_table)
    {
        for(int i{0}; i < m_columns; i++)
        {
            row.push_back(column++);
        }
    }
}

void Board::coverBoardSlot(const int tablePosition, const int currentPlayer)
{
    for(auto& row : m_table)
    {
        for(auto& column : row)
        {
            if(column == tablePosition)
            {
                column = currentPlayer;
                return;
            }
        }
    }
}

//Win Logic
bool Board::isWinningMove(const int playerMark) const
{
    if(this -> isLateralWin(playerMark))
    {
        m_winCase = WinCase::Lateral;
        return true;
    }
    else if(this -> isVerticalWin(playerMark))
    {
        m_winCase = WinCase::Vertical;
        return true;
    }
    else if (this -> isDiagonalWin(playerMark))
    {
        m_winCase = WinCase::Diagonal;
        return true;
    }
    return false;
}

bool Board::isLateralWin(const int playerMark) const
{
    int inARow{};
    for(const auto& row : m_table)
    {
        for(const auto& column : row)
        {
            if(column == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_columns)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::isVerticalWin(const int playerMark) const
{
    int inARow{};
    for(int column{0}; column < m_columns; column++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row][column] == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_rows)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::isDiagonalWin(const int playerMark) const
{
    if(m_evenBoard)
    {
        return this -> evenBoard(playerMark);
    }
    else if(m_rows < m_columns)
    {
        return this -> lopSidedRow(playerMark);
    }
    else if (m_columns < m_rows)
    {
        return this -> lopSidedColumn(playerMark);
    }
    return false;
}

//Diagonal subcases
bool Board::evenBoard(const int playerMark) const
{
    int inARow{};
    for(int row{0}, column{0}; row < m_rows; row++, column++)
    {
        if(m_table[row][column] == playerMark)
        {
            inARow++;
        }
    }
    if(inARow == m_rows)
    {
        return true;
    }
    inARow = 0;

    //Reverse case
    for(int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
    {
        if(m_table[row].at(columnOffSet - row) == playerMark)
        {
            inARow++;
        }
    }
    if(inARow == m_rows)
    {
        return true;
    }
    return false;
}


/*
    *NOTE: if rows < columns, columns - rows = only diagonal cases(Column Based)
    *ex. 4x8: Diagona cases: column: 0, 1, 2, 3, 4 index based!
    *10x11: Diagona cases: column: 0, 1
    *
*/
bool Board::lopSidedRow(const int playerMark) const
{
    int inARow{};
    int offSet{m_columns -  m_rows};
    for(int column{0}; column <= offSet; column++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(column + row) == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_rows)
        {
            return true;
        }
        inARow = 0;
    }
    inARow = 0;

    //Reverse case
    for(int column{m_columns - 1}; column >= ((m_columns - 1) - offSet);
        column--)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(column - row) == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_rows)
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
    *ex. 8x4: Diagona cases: row: 0, 1, 2, 3, 4 index based!
    *15x11: Diagona cases: row: 0, 1, 2, 3, 4
*/
bool Board::lopSidedColumn(const int playerMark) const
{
    int inARow{};
    int offSet{m_rows -  m_columns};
    for(int loop{0}; loop <= offSet; loop++)
    {
        for(int row{0}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(loop + row)[row] == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_columns)
        {
            return true;
        }
        inARow = 0;
    }
    inARow = 0;

    //Reverse case
    for(int loop{0}; loop <= offSet; loop++)
    {
        for(int row{0}, column{m_columns - 1}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(row + loop).at(column - row) == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_columns)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::isTie(const int playerX, const int playerO) const
{
    int totalPlayerMarks{};
    for(const auto& row : m_table)
    {
        for(const auto& column : row)
        {
            if(column == playerX || column == playerO)
            {
                totalPlayerMarks++;
            }
        }
    }
    if(totalPlayerMarks == m_boardSize)
    {
        return true;
    }
    return false;
}

std::string_view Board::winCase() const
{
    switch(m_winCase)
    {
        case WinCase::Lateral:
            return "Lateral";
            break;
        case WinCase::Vertical:
            return "Vertical";
            break;
        case WinCase::Diagonal:
            return "Diagonal";
            break;
    }
    return "";
}

//Util
void Board::resetBoard()
{
    m_table.clear();
    m_rows = 0;
    m_columns = 0;
    if(m_evenBoard)
    {
        m_evenBoard = false;
    }
}

#ifdef BOARDDEBUG
//TODO: bug fixes
//methods to set diff win conditions
bool Board::isValidWinCase(int startPoint, WinCase winCase,
                           bool reverseCase) const
{
    static const ValidWinCases winCases{validLateralWinCases(),
    validVerticalWinCases(), validDiagonalWinCases()};
    switch(winCase)
    {
        case Board::WinCase::Lateral:
            return isValidWin(winCases.m_lateralCases, startPoint);
        case Board::WinCase::Vertical:
            return isValidWin(winCases.m_verticalCases, startPoint);
        case Board::WinCase::Diagonal:
            return isValidDiagonalWin(winCases.m_diagonalCases, startPoint,
                              reverseCase);
    }
    return false;
}

bool Board::isValidWin(const std::vector<int>& winCases,
                       const int startPoint) const
{
    for(const int winCase: winCases)
    {
        if(winCase == startPoint)
        {
            return true;
        }
    }
    return false;
}

bool Board::isValidDiagonalWin(const std::vector<int>& winCases,
                               const int startPoint,
                               const bool reverseCase) const
{
    static int n{static_cast<int>(winCases.size())};
    static int offSet{n / 2};
    if(!reverseCase)
    {
        for(int i{0}; i < offSet; ++i)
        {
            if(winCases[i] == startPoint)
            {
                return true;
            }
        }
    }
    //reverse cases will always be the last [offset] number of elements in vec
    // offset to (vec size - 1)
    else
    {
        for(int i{offSet}; i <= (n - 1); ++i)
        {
            if(winCases[i] == startPoint)
            {
                return true;
            }
        }
    }
    return false;
}
const std::vector<int> Board::validLateralWinCases() const
{
    std::vector<int> winCases{};
    for(int row{0}; row < m_rows; ++row)
    {
        winCases.push_back(m_table[row][0]);
    }
    return winCases;
}

const std::vector<int> Board::validVerticalWinCases() const
{
    return m_table[0];
}

const std::vector<int> Board::validDiagonalWinCases() const
{
    std::vector<int> winCases{};
    int offSet{};
    if(m_rows < m_columns)
    {
        offSet = m_columns - m_rows;
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table[0].at(i));
        }
        //reverse cases
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table[0].at((m_columns - 1) - i));
        }
        return winCases;
    }
    else if(m_columns < m_rows)
    {
        offSet = m_rows - m_columns;
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table.at(i)[0]);
        }
        //reverseCases
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table.at(i)[m_columns - 1]);
        }
        return winCases;
    }
    return winCases;
}

void Board::setLateralWin(const int row, const int playerMark)
{
    if(!this -> isValidWinCase(row, WinCase::Lateral))
    {
        std::cout << "Invalid row!\n";
        return;
    }
    for(int fill{row}, endColumn{row + m_columns}; fill < endColumn; fill++)
    {
        this -> coverBoardSlot(fill, playerMark);
    }
}

void Board::setVerticalWin(const int column, const int playerMark)
{
    if(!this -> isValidWinCase(column, WinCase::Vertical))
    {
        std::cout << "Invalid column!\n";
        return;
    }
    for(int row{0}, columnOffset{column}; row < m_rows;
        row++, columnOffset += m_columns)
    {
        this -> coverBoardSlot(columnOffset, playerMark);
    }
}

void Board::setTie(const int playerMark)
{
    for(int fill{1}; fill <= m_boardSize; fill++)
    {
        this -> coverBoardSlot(fill, playerMark);
    }
}

void Board::setDiagonalWin(int startColumn, const int playerMark,
                           const bool reverseCase)
{
    if(m_evenBoard)
    {
        return this -> setDiagonalWinEvenBoard(playerMark, reverseCase);
    }
    else if(this -> isValidWinCase(startColumn, WinCase::Diagonal, reverseCase))
    {
        if(m_rows < m_columns)
        {
            return this -> setDiagonalWinLopSidedRow(startColumn, playerMark,
                                                     reverseCase);
        }
        else if (m_columns < m_rows)
        {
            return this -> setDiagonalWinLopSidedColumn(startColumn, playerMark,
                                                        reverseCase);
        }
    }
    std::cout << "Invalid column!\n";
}

void Board::setDiagonalWinEvenBoard(const int playerMark, bool reverseCase)
{
    if(!reverseCase)
    {
        for(int row{0}, column{0}; row < m_rows; row++, column++)
        {
            this -> coverBoardSlot(m_table[row][column], playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
        {
            this -> coverBoardSlot(m_table[row].at(columnOffSet - row),
                                   playerMark);
        }
    }
}

void Board::setDiagonalWinLopSidedRow(int startColumn, const int playerMark,
                               const bool reverseCase)
{
    --startColumn;
    if(!reverseCase)
    {
        for(int row{0}, column{startColumn}; row < m_rows; row++)
        {
            this -> coverBoardSlot(m_table[row].at(column + row),
                                   playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int row{0}, column{startColumn}; row < m_rows; row++)
        {
            this -> coverBoardSlot(m_table[row].at(column - row),
                                   playerMark);
        }
    }
}

void Board::setDiagonalWinLopSidedColumn(int startColumn, const int playerMark,
                               const bool reverseCase)
{
    if(!reverseCase)
    {
        for(int column{0}; column < m_columns; ++column,
            startColumn += (m_columns + 1))
        {
            this -> coverBoardSlot(startColumn, playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int column{0}; column < m_columns; ++column,
            startColumn += (m_columns - 1))
        {
            this -> coverBoardSlot(startColumn, playerMark);
        }
    }
}
#endif
//Private Methods

//Methods to help with display formatting
//Positive ints only!
bool Board::isSingleDigit(const int column)
{
    return column < 10;
}

bool Board::isDoubleDigit(const int column)
{
    return column >= 10 && column < 100;
}

bool Board::isTripleDigit(const int column)
{
    return column >= 100 && column < 1000;
}

void Board::dashLine() const
{
    for(int dashLine{0}; dashLine < m_columns; dashLine++)
    {
        if(dashLine == 0)
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
//END PRIVATE METHODS
//END PUBLIC METHODS
