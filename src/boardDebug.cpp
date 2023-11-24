#include "board.h"

#ifdef BOARD_DEBUG
//TODO: implement clearDiaWin

//Currently working on:
void Board::clearWinConfiguration(const int playerMark)
{
    if(m_winCase == WinCase::NoWinCase)
    {
        return;
    }
    if(_multipleWinCases(playerMark))
    {
        this -> setBoard(m_rows, m_columns);
        return;
    }
    switch(m_winCase)
    {
        case WinCase::Lateral:
            _clearLateralWin(playerMark);
            break;
        case WinCase::Vertical:
            _clearVerticalWin(playerMark);
            break;
        case WinCase::Diagonal:
            //The work required to undo a single diagonal win case isn't worth
            //the headache. <----- I lied.
            //this -> setBoard(m_rows, m_columns);
            _clearDiagonalWin(playerMark);
            break;
        case WinCase::NoWinCase:
            return;
    }
    m_winCase = WinCase::NoWinCase;
}

//methods to set diff win conditions
bool Board::setLateralWin(const int startRow, const int playerMark)
{
    if(!_isValidWinCase(startRow, WinCase::Lateral))
    {
        std::cout << "setLatWin(): Invalid row!\n";
        return false;
    }
    for(int tablePosition{startRow}, endColumn{startRow + m_columns};
        tablePosition < endColumn; tablePosition++)
    {
        this -> coverBoardSlot(tablePosition, playerMark);
    }
    m_winCase = WinCase::Lateral;
    return true;
}

bool Board::setVerticalWin(const int startColumn, const int playerMark)
{
    if(!_isValidWinCase(startColumn, WinCase::Vertical))
    {
        std::cout << "setVertWin(): Invalid column!\n";
        return false;
    }
    for(int row{0}, columnOffset{startColumn}; row < m_rows;
        row++, columnOffset += m_columns)
    {
        this -> coverBoardSlot(columnOffset, playerMark);
    }
    m_winCase = WinCase::Vertical;
    return true;
}

bool Board::setTie(const int playerMark)
{
    for(int tablePosition{1}; tablePosition <= m_boardSize; tablePosition++)
    {
        this -> coverBoardSlot(tablePosition, playerMark);
    }
    return true;
}

bool Board::setDiagonalWin(int startColumn, const int playerMark,
                           const bool reverseWin)
{
    if(_isValidWinCase(startColumn, WinCase::Diagonal, reverseWin) &&
            !m_evenBoard)
    {
        if(m_rows < m_columns)
        {
            _setDiagonalWinLopsidedRow(startColumn, playerMark,
                                                     reverseWin);
        }
        else if (m_columns < m_rows)
        {
            _setDiagonalWinLopsidedColumn(startColumn, playerMark,
                                                        reverseWin);
        }
    }
    //if winCase is invalid but board is even, winCase isn't needed
    //only reverse case
    else if(m_evenBoard)
    {
        _setDiagonalWinEvenBoard(playerMark, reverseWin);
    }
    else
    {
        std::cout << "setDiaWin(): " << ((m_rows < m_columns)
                                         ? "Invalid Column!\n"
                                         : "Invalid Row!\n");
        return false;
    }
    m_diagonalReverseWin = reverseWin;
    m_winCase = WinCase::Diagonal;
    return true;
}

//Util methods for setDiaWin
void Board::_setDiagonalWinEvenBoard(const int playerMark, bool reverseWin)
{
    if(!reverseWin)
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

void Board::_setDiagonalWinLopsidedRow(int startColumn, const int playerMark,
                               const bool reverseWin)
{
    //convert to index as columns in the rows are not 0 indexed
    --startColumn;
    if(!reverseWin)
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

void Board::_setDiagonalWinLopsidedColumn(int startRow, const int playerMark,
                               const bool reverseWin)
{
    if(!reverseWin)
    {
        for(int column{0}; column < m_columns; ++column,
            startRow += (m_columns + 1))
        {
            this -> coverBoardSlot(startRow, playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int column{0}; column < m_columns; ++column,
            startRow += (m_columns - 1))
        {
            this -> coverBoardSlot(startRow, playerMark);
        }
    }
}

//Util methods for all win case set'ers
bool Board::_isValidWinCase(const int startPoint, const WinCase winCase,
                           const bool reverseWin) const
{
    static int currentBoardSize{m_boardSize};
    ValidWinCases winCases
    {
        _validLateralWinCases(),
        _validVerticalWinCases(),
        _validDiagonalWinCases()
    };

    if (currentBoardSize != m_boardSize)
    {
        currentBoardSize = m_boardSize;

        winCases.m_lateralCases.clear();
        winCases.m_verticalCases.clear();
        winCases.m_diagonalCases.clear();

        //Have to do this as you cannot assign a vector to an already made vector
        for(int winCase : _validLateralWinCases())
        {
            winCases.m_lateralCases.push_back(winCase);
        }
        for (int winCase : _validVerticalWinCases())
        {
            winCases.m_verticalCases.push_back(winCase);
        }
        for (int winCase : _validDiagonalWinCases())
        {
            winCases.m_diagonalCases.push_back(winCase);
        }  
    }

    switch(winCase)
    {
        case WinCase::Lateral:
            return _isValidWin(winCases.m_lateralCases, startPoint);
        case WinCase::Vertical:
            return _isValidWin(winCases.m_verticalCases, startPoint);
        case WinCase::Diagonal:
            return _isValidDiagonalWin(winCases.m_diagonalCases,
                                              startPoint, reverseWin);
        case WinCase::NoWinCase:
           break;
    }
    return false;
}

//Util methods for isValidWinCase
bool Board::_isValidWin(const std::vector<int>& winCases,
                       const int startPoint)
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

bool Board::_isValidDiagonalWin(const std::vector<int>& winCases,
                               const int startPoint,
                               const bool reverseWin)
{
    const static int n{static_cast<int>(winCases.size())};
    const static int offSet{n / 2};
    if(!reverseWin)
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
    // offset to vec size
    else
    {
        for(int i{offSet}; i < n; ++i)
        {
            if(winCases[i] == startPoint)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Board::_validLateralWinCases() const
{
    std::vector<int> winCases{};
    for(int row{0}; row < m_rows; ++row)
    {
        winCases.push_back(m_table[row][0]);
    }
    return winCases;
}

std::vector<int> Board::_validVerticalWinCases() const
{
    return m_table[0];
}

std::vector<int> Board::_validDiagonalWinCases() const
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
    }
    else if(m_columns < m_rows)
    {
        offSet = m_rows - m_columns;
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table.at(i)[0]);
        }
        //reverseWins
        for(int i{0}; i <= offSet; ++i)
        {
            winCases.push_back(m_table.at(i)[m_columns - 1]);
        }
    }
    return winCases;
}

//Util methods for clearWinConfig
void Board::_clearLateralWin(const int playerMark)
{
    int offSet{};
    for(int row{0}; row < m_rows; ++row)
    {
        for(int column{0}; column < m_columns; ++column)
        {
            if(m_table[row][column] == playerMark)
            {
                if(row == 0)
                {
                    for(int i{0}; i <= m_columns; ++i)
                    {
                        m_table[row][i] = i + 1;
                    }
                    return;
                }
                else
                {
                    offSet = m_table[row - 1][m_columns - 1] + 1;
                    for(int i{0}; i < m_columns; ++i)
                    {
                        m_table[row][i] = offSet++;
                    }
                    return;
                }
            }
        }
    }
}

void Board::_clearVerticalWin(const int playerMark)
{
    for(int row{0}; row < m_rows; ++row)
    {
        for(int column{0}; column < m_columns; ++column)
        {
            if(column == 0)
            {
                if(m_table[row][column] == playerMark)
                {
                    m_table[row][column] = m_table[row][column + 1] - 1;
                }
            }
            else
            {
                if(m_table[row][column] == playerMark)
                {
                    m_table[row][column] = m_table[row][column - 1] + 1;
                }
            }
        }
    }
}

void Board::_clearDiagonalWin(const int playerMark)
{
    if (m_rows < m_columns)
    {
        _clearDiagonalWinLopsidedRow(playerMark,
            m_diagonalReverseWin);
    }
    else if (m_columns < m_rows)
    {
        _clearDiagonalWinLopsidedColumn(playerMark,                            
            m_diagonalReverseWin);
    }
    else if (m_evenBoard)
    {
        _clearDiagonalWinEvenBoard(m_diagonalReverseWin);
    }
}

void Board::_clearDiagonalWinEvenBoard(const bool reverseWin)
{
    int startPoint{};
    if (!reverseWin)
    {
        startPoint = m_table[0][1] - 1 ;
        for (int row{ 0 }, column{0}; row < m_columns; ++row, ++column, startPoint += (m_columns + 1))
        {
            m_table[row][column] = startPoint;
        }
    }
    else
    {  
        startPoint = m_table[0].at(static_cast<size_t>((m_columns - 2))) + 1 ;
        for (int row{0}, columnOffset{m_columns - 1}; row < m_columns; ++row, --columnOffset, startPoint += m_columns)
        {
            m_table[row][columnOffset] = startPoint;
        }
    }
}

//When looping to find the startPoint, it will only be valid if the playerMark found is from a column of the first row
//ReverseWin: When looping to find the startPoint, it will only be valid if the playerMark found is from a column of the first row
void Board::_clearDiagonalWinLopsidedRow(const int playerMark, const bool reverseWin)
{

}
//When looping to find the startPoint, it will only be valid if the playerMark found is from the starting column of each row
//ReverseWin: When looping to find the startPoint, it will only be valid if the playerMark found is from the ending column of each row
void Board::_clearDiagonalWinLopsidedColumn(const int playerMark, const bool reverseWin)
{

}


bool Board::_multipleWinCases(const int playerMark) const
{
    int winCaseCount{};
    if(_isLateralWin(playerMark))
    {
        ++winCaseCount;
    }
    if(_isVerticalWin(playerMark))
    {
        ++winCaseCount;
    }
    //isDia does a lot of looping, only call if you have to.
    if(winCaseCount == 0)
    {
        return false;
    }
    else if(winCaseCount > 1)
    {
        return true;
    }
    if(_isDiagonalWin(playerMark))
    {
        ++winCaseCount;
    }
    return (winCaseCount > 1);
}
#endif //BOARD_DEBUG
