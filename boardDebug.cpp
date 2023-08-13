#include "board.h"

#ifdef BOARDDEBUG
//TODO: implement clearDiaWin
//methods to set diff win conditions

//Will not work if multiple win conditions are set
void Board::clearWinConfiguration(const int playerMark)
{
    switch(m_winCase)
    {
        case WinCase::Lateral:
            this -> clearLateralWin(playerMark);
            break;
        case WinCase::Vertical:
            this -> clearVerticalWin(playerMark);
            break;
        case WinCase::Diagonal:
            break;
        case WinCase::NoWinCase:
            return;
    }
    m_winCase = WinCase::NoWinCase;
}

void Board::clearLateralWin(const int playerMark)
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
                }
                else
                {
                    offSet = m_table[row - 1][m_columns - 1] + 1;
                    for(int i{0}; i < m_columns; ++i)
                    {
                        m_table[row][i] = offSet++;
                    }
                }
            }
        }
    }
}

void Board::clearVerticalWin(const int playerMark)
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
    m_winCase = WinCase::Lateral;
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
    m_winCase = WinCase::Vertical;
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
        this -> setDiagonalWinEvenBoard(playerMark, reverseCase);
    }
    else if(this -> isValidWinCase(startColumn, WinCase::Diagonal, reverseCase))
    {
        if(m_rows < m_columns)
        {
            this -> setDiagonalWinLopSidedRow(startColumn, playerMark,
                                                     reverseCase);
        }
        else if (m_columns < m_rows)
        {
            this -> setDiagonalWinLopSidedColumn(startColumn, playerMark,
                                                        reverseCase);
        }
    }
    else
    {
        std::cout << "Invalid column!\n";
        return;
    }
    m_winCase = WinCase::Diagonal;
}

//Util funcs for setDiaWin
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
    //convert to index as columns in the rows are not 0 indexed
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

void Board::setDiagonalWinLopSidedColumn(int startRow, const int playerMark,
                               const bool reverseCase)
{
    if(!reverseCase)
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

bool Board::isValidWinCase(const int startPoint, const WinCase winCase,
                           const bool reverseCase) const
{
    //static so winCases aren't re-calculated every func call
    static const ValidWinCases winCases{validLateralWinCases(),
    validVerticalWinCases(), validDiagonalWinCases()};
    switch(winCase)
    {
        case Board::WinCase::Lateral:
            return this -> isValidWin(winCases.m_lateralCases, startPoint);
        case Board::WinCase::Vertical:
            return this -> isValidWin(winCases.m_verticalCases, startPoint);
        case Board::WinCase::Diagonal:
            return this -> isValidDiagonalWin(winCases.m_diagonalCases,
                                              startPoint, reverseCase);
        case Board::WinCase::NoWinCase:
            return false;
    }
    return false;
}

//Util funcs for isValidWinCase
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
#endif
