#include "board.h"
using namespace BoardTypes;

//Constructors
Board::Board(const int row, const int column)
    : m_table{}
    , m_winCase{WinCase::NoWinCase}
    , m_rows{}
    , m_columns{}
    , m_boardSize{}
    , m_evenBoard{}
{
    if(row >= 3 && column >= 3)
    {
        setBoard(row, column);
    }
}

//Table Logic
void Board::display() const
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
    _dashLine();
    for (const auto& row : m_table)
    {
        std::cout << "|";
        for (const auto& column : row)
        {
            if (column.m_playerIsOccupying)
            {
                std::cout << " " << column.m_playerFlag << "  |";
                //                std::cout << " " << column << " |";
            }
            else
            {//  |1   |2   |3   |
                if (Board::_isSingleDigit(column.m_piecePosition))
                {
                    std::cout << " " << column.m_piecePosition << "  |";
                }//  |14  |15  |16  |
                else if (Board::_isDoubleDigit(column.m_piecePosition))
                {
                    std::cout << " " << column.m_piecePosition << " |";
                }//|700 |800 |900 |
                else if (Board::_isTripleDigit(column.m_piecePosition))
                {
                    std::cout << " " << column.m_piecePosition << "|";
                }//1000|2000|3000
                else
                {
                    std::cout << column.m_piecePosition << "|";
                }
            }
        }
        std::cout << '\n';
        _dashLine();
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

void Board::setBoard(const int rows, const int columns)
{
    if(!isEmpty())
    {
        resetBoard();
    }
    m_rows = rows;
    m_columns = columns;
    m_boardSize = m_rows * m_columns;

    if(m_rows == m_columns)
    {
        m_evenBoard = true;
    }

    m_table.reserve(m_rows);
    for (int row{ 0 }; row < m_rows; row++)
    {
        m_table.push_back(std::vector<BoardPiece>{});
    }

    int column{ 1 };
    for (auto& row : m_table)
    {
        for (int i{ 0 }; i < m_columns; i++)
        {
            row.push_back(BoardPiece{ column++ });
        }
    }
}

void Board::coverBoardSlot(const int tablePosition, const char currentPlayer)
{
    for (auto& row : m_table)
    {
        for (auto& column : row)
        {
            if (column.m_piecePosition == tablePosition)
            {
                column.m_playerFlag = currentPlayer;
                column.m_playerIsOccupying = true;
                return;
            }
        }
    }
}



//Win Logic
bool Board::isWinningMove(const char playerMark) const
{
    if(_isLateralWin(playerMark))
    {
        m_winCase = WinCase::Lateral;
        return true;
    }
    else if(_isVerticalWin(playerMark))
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
bool Board::_isLateralWin(const char playerMark) const
{
    int inARow{};
    for(const auto& row : m_table)
    {
        for(const auto& column : row)
        {
            if (column.m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
        }
        if(inARow == m_columns)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::_isVerticalWin(const char playerMark) const
{
    int inARow{};
    for(int column{0}; column < m_columns; column++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if (m_table[row][column].m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
        }
        if(inARow == m_rows)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::_isDiagonalWin(const char playerMark) const
{
    if(m_evenBoard)
    {
        return _evenBoard(playerMark);
    }
    else if(m_rows < m_columns)
    {
        return _lopsidedRow(playerMark);
    }
    else if (m_columns < m_rows)
    {
        return _lopsidedColumn(playerMark);
    }
    return false;
}

//Util methods for isDiaWin
bool Board::_evenBoard(const char playerMark) const
{
    int inARow{};
    for(int row{0}, column{0}; row < m_rows; row++, column++)
    {
        if (m_table[row][column].m_playerFlag == playerMark)
        {
            inARow++;
            continue;
        }
        break;
    }
    if(inARow == m_rows)
    {
        return true;
    }
    inARow = 0;

    //Reverse case
    for(int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
    {
        if (m_table[row].at(static_cast<size_t>(columnOffSet - row)).m_playerIsOccupying)
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
bool Board::_lopsidedRow(const char playerMark) const
{
    int inARow{};
    int offSet{m_columns -  m_rows};

    for(int column{0}; column <= offSet; column++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if (m_table[row].at(static_cast<size_t>(column + row)).m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
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
            if (m_table[row].at(static_cast<size_t>(column - row)).m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
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
    *ex. 8x4: Diagonal cases: row: 0, 1, 2, 3, 4 index based!
    *15x11: Diagonal cases: row: 0, 1, 2, 3, 4
*/
bool Board::_lopsidedColumn(const char playerMark) const
{
    int inARow{};
    int offSet{m_rows -  m_columns};
    for(int loop{0}; loop <= offSet; loop++)
    {

        for(int row{0}; row < (m_rows - offSet); row++)
        {
            if (m_table.at(static_cast<size_t>(loop + row))[row].m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
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
            if (m_table.at(static_cast<size_t>(row + loop)).at(static_cast<size_t>(column - row)).m_playerFlag == playerMark)
            {
                inARow++;
                continue;
            }
            break;
        }
        if(inARow == m_columns)
        {
            return true;
        }
        inARow = 0;
    }
    return false;
}

bool Board::isTie() const
{
    int totalPlayerMarks{};
    for(const auto& row : m_table)
    {
        for(const auto& column : row)
        {
            if(column.m_playerIsOccupying)
            {
                totalPlayerMarks++;
                continue;
            }
            return false;
        }
    }
    return (totalPlayerMarks == m_boardSize);
}


//Util Logic
std::string_view Board::winCase() const
{
    switch(m_winCase)
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

void Board::resetBoard()
{
    m_table.clear();
    m_rows = 0;
    m_columns = 0;
    if(m_evenBoard)
    {
        m_evenBoard = false;
    }
    m_winCase = WinCase::NoWinCase;
}

//Methods to help with display formatting
//Positive ints only!
bool Board::_isSingleDigit(const int column)
{
    return column < 10;
}

bool Board::_isDoubleDigit(const int column)
{
    return column >= 10 && column < 100;
}

bool Board::_isTripleDigit(const int column)
{
    return column >= 100 && column < 1000;
}

void Board::_dashLine() const
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
//

bool Board::isEmpty() const
{
    return m_table.empty();
}