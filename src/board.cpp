#include "board.h"

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
    _dashLine();
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
                if(_isSingleDigit(column))
                {
                    std::cout << " " << column << "  |";
                }//  |14  |15  |16  |
                else if(_isDoubleDigit(column))
                {
                    std::cout << " " << column << " |";
                }//|700 |800 |900 |
                else if(_isTripleDigit(column))
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
    //O(n) + O(nm) = O(nm + n) ||
    //O(n) + O(n^2)
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
    //O(n)
    for(int row{0}; row < m_rows; row++)
    {
        m_table.push_back(std::vector<int>{});
    }

    int column{1};
    //if n == m || n > m, O(n^2)
    //O(nm) || O(n^2)
    for(auto& row : m_table)
    {
        //O(m)
        for(int i{0}; i < m_columns; i++)
        {
            row.push_back(column++);
        }
    }
}

void Board::coverBoardSlot(const int tablePosition, const int currentPlayer)
{
    //if n == m || n > m, O(n^2)
    //O(n) * O(m) = O(nm)
    //O(n)
    for(auto& row : m_table)
    {
        //O(m)
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
    if(_isLateralWin(playerMark))//O(nm) || O(n^2)
    {
        m_winCase = WinCase::Lateral;
        return true;
    }
    else if(_isVerticalWin(playerMark))//O(nm) || O(n^2)
    {
        m_winCase = WinCase::Vertical;
        return true;
    }
    else if (_isDiagonalWin(playerMark))//O(n) || O(nm) || O(n^2)
    {
        m_winCase = WinCase::Diagonal;
        return true;
    }
    return false;
}

//Util methods for isWinningMove
bool Board::_isLateralWin(const int playerMark) const
{
    //if n == m || n > m, O(n^2)
    //O(n) * O(m) = O(nm)
    int inARow{};
    //O(n)
    for(const auto& row : m_table)
    {
        //O(m)
        for(const auto& column : row)
        {
            if(column == playerMark)
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

bool Board::_isVerticalWin(const int playerMark) const
{
    //if n == m || n > m, O(n^2)
    //O(n) * O(m) = O(nm)
    int inARow{};
    //O(n)
    for(int column{0}; column < m_columns; column++)
    {
        //O(m)
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row][column] == playerMark)
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

bool Board::_isDiagonalWin(const int playerMark) const
{
    //O(n)
    if(m_evenBoard)
    {
        return _evenBoard(playerMark);
    }
    //For both lopsided methods:
    //O(n * m) + O(n * m) = O(2nm) = O(nm)
    //if n == m || n > m, O(n^2)
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
bool Board::_evenBoard(const int playerMark) const
{
    //O(n) + O(n) = O(2n) = O(n)
    int inARow{};
    //O(n)
    for(int row{0}, column{0}; row < m_rows; row++, column++)
    {
        if(m_table[row][column] == playerMark)
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
    //O(n)
    for(int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
    {
        if(m_table[row].at(columnOffSet - row) == playerMark)
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
bool Board::_lopsidedRow(const int playerMark) const
{
    //O(n * m) + O(n * m) = O(2nm) = O(nm)
    //if n == m || n > m, O(n^2)
    int inARow{};
    int offSet{m_columns -  m_rows};
    //O(n)
    for(int column{0}; column <= offSet; column++)
    {
        //O(m)
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(column + row) == playerMark)
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
    //O(n)
    for(int column{m_columns - 1}; column >= ((m_columns - 1) - offSet);
        column--)
    {
        //O(m)
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(column - row) == playerMark)
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
bool Board::_lopsidedColumn(const int playerMark) const
{
    //O(n * m) + O(n * m) = O(2nm) = O(nm)
    //if n == m || n > m, O(n^2)
    int inARow{};
    int offSet{m_rows -  m_columns};
    //O(n)
    for(int loop{0}; loop <= offSet; loop++)
    {
        //O(m)
        for(int row{0}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(loop + row)[row] == playerMark)
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
    //O(n)
    for(int loop{0}; loop <= offSet; loop++)
    {
        //O(m)
        for(int row{0}, column{m_columns - 1}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(row + loop).at(column - row) == playerMark)
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

bool Board::isTie(const int playerX, const int playerO) const
{
    //O(n * m) = O(nm)
    int totalPlayerMarks{};
    //O(n)
    for(const auto& row : m_table)
    {
        //O(m)
        for(const auto& column : row)
        {
            if(column == playerX || column == playerO)
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
    //O(n)
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