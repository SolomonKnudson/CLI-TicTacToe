#include "board.h"

#ifdef BOARD_DEBUG
using namespace BoardTypes;
//TODO: implement both _clearDiagonalWinLopsided()

//methods to set diff win conditions
bool Board::setLateralWin(const int startRow, const char playerMark)
{
    if(!_isValidWinCase(startRow, WinCase::Lateral))
    {
        std::cout << "setLatWin(): Invalid row!\n";
        return false;
    }

    for(int tablePosition{startRow}, endColumn{startRow + m_columns};
        tablePosition < endColumn; tablePosition++)
    {
        coverBoardSlot(tablePosition, playerMark);
    }

    m_winCase = WinCase::Lateral;
    return true;
}

bool Board::setVerticalWin(const int startColumn, const char playerMark)
{
    if(!_isValidWinCase(startColumn, WinCase::Vertical))
    {
        std::cout << "setVertWin(): Invalid column!\n";
        return false;
    }
    for(int row{0}, columnOffset{startColumn}; row < m_rows;
        row++, columnOffset += m_columns)
    {
        coverBoardSlot(columnOffset, playerMark);
    }
    m_winCase = WinCase::Vertical;
    return true;
}

bool Board::setTie(const char playerMark)
{
    for(int tablePosition{1}; tablePosition <= m_boardSize; tablePosition++)
    {
        coverBoardSlot(tablePosition, playerMark);
    }
    return true;
}

bool Board::setDiagonalWin(int startColumn, const char playerMark,
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
void Board::_setDiagonalWinEvenBoard(const char playerMark, bool reverseWin)
{
    if(!reverseWin)
    {
        for(int row{0}, column{0}; row < m_rows; row++, column++)
        {
            coverBoardSlot(m_table[row][column].m_piecePosition, playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int row{0}, columnOffSet{m_columns - 1}; row < m_rows; row++)
        {
            coverBoardSlot(m_table[row]
                .at(static_cast<size_t>(columnOffSet - row)).m_piecePosition, 
                playerMark);
        }
    }
}

void Board::_setDiagonalWinLopsidedRow(int startColumn, const char playerMark,
                               const bool reverseWin)
{
    //convert to index as columns in the rows are not 0 indexed
    --startColumn;
    if(!reverseWin)
    {
        for(int row{0}, column{startColumn}; row < m_rows; row++)
        {
            coverBoardSlot(m_table[row]
                .at(static_cast<size_t>(column + row)).m_piecePosition,
                                   playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int row{0}, column{startColumn}; row < m_rows; row++)
        {
            coverBoardSlot(m_table[row]
                .at(static_cast<size_t>(column - row)).m_piecePosition,
                                   playerMark);
        }
    }
}

void Board::_setDiagonalWinLopsidedColumn(int startRow, const char playerMark,
                               const bool reverseWin)
{
    if(!reverseWin)
    {
        for(int column{0}; column < m_columns; ++column,
            startRow += (m_columns + 1))
        {
            coverBoardSlot(startRow, playerMark);
        }
    }
    else
    {
        //Reverse case
        for(int column{0}; column < m_columns; ++column,
            startRow += (m_columns - 1))
        {
            coverBoardSlot(startRow, playerMark);
        }
    }
}
#endif //BOARD_DEBUG
