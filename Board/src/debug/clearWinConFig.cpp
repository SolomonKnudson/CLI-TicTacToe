#include "board.h"

#ifdef BOARD_DEBUG
using namespace BoardTypes;

void Board::clearWinConfiguration(const char playerMark)
{
    if (m_winCase == WinCase::NoWinCase)
    {
        return;
    }

    if (_multipleWinCases(playerMark))
    {
        setBoard(m_rows, m_columns);
        return;
    }

    switch (m_winCase)
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
        _clearDiagonalWin(playerMark);
        break;
    case WinCase::NoWinCase:
        return;
    }

    m_winCase = WinCase::NoWinCase;
}

//Util methods for clearWinConfig
void Board::_clearLateralWin(const char playerMark)
{
    int offSet{};
    for (int row{ 0 }; row < m_rows; ++row)
    {
        for (int column{ 0 }; column < m_columns; ++column)
        {
            if (m_table[row][column].m_playerFlag == playerMark)
            {
                m_table[row][column].reset();
            }

        }
    }
}

void Board::_clearVerticalWin(const char playerMark)
{
    for (int row{ 0 }; row < m_rows; ++row)
    {
        for (int column{ 0 }; column < m_columns; ++column)
        {
            if (column == 0)
            {
                if (m_table[row][column].m_playerFlag == playerMark)
                {
                    m_table[row][column].reset();
                }
            }
            else
            {
                if (m_table[row][column].m_playerFlag == playerMark)
                {
                    m_table[row][column].reset();
                }
            }
        }
    }
}

void Board::_clearDiagonalWin(const char playerMark)
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
        _clearDiagonalWinEvenBoard(playerMark, m_diagonalReverseWin);
    }
}

void Board::_clearDiagonalWinEvenBoard(const char playerMark, const bool reverseWin)
{
    int startPoint{};
    if (!reverseWin)
    {
        startPoint = m_table[0][1].m_piecePosition - 1;
        for (int row{ 0 }, column{ 0 }; row < m_columns; ++row, ++column, 
            startPoint += (m_columns + 1))
        {
            if (m_table[row][column].m_playerFlag == playerMark)
            {
                m_table[row][column].reset();
            }
        }
    }
    else
    {
        startPoint = m_table[0].at(static_cast<size_t>((m_columns - 2))).m_piecePosition + 1;
        for (int row{ 0 }, columnOffset{ m_columns - 1 }; row < m_columns; ++row, 
            --columnOffset, startPoint += m_columns)
        {
            if (m_table[row][columnOffset].m_playerFlag == playerMark)
            {
                m_table[row][columnOffset].reset();
            }
        }
    }
}



//When looping to find the startPoint, it will only be valid if the playerMark found is from a column of the first row
//ReverseWin: When looping to find the startPoint, it will only be valid if the playerMark found is from a column of the first row
void Board::_clearDiagonalWinLopsidedRow(const char playerMark, const bool reverseWin)
{
    int columnOffSet{ m_columns - m_rows };
    if (!reverseWin)
    {
        for (int columnStart{ 0 }; columnStart <= columnOffSet; ++columnStart)
        {
            if (m_table[0][columnStart].m_playerFlag == playerMark)
            {
                for (int row{ 0 }, column{ columnStart }; row < m_rows; ++row, ++column)
                {
                    if (m_table[row][column].m_playerFlag == playerMark)
                    {
                        m_table[row][column].reset();
                    }
                }
            }
        }
    }
    else
    {
        for (int numberOfLoops{ 0 }, columnStart{ m_columns - 1 }; 
            numberOfLoops <= columnOffSet; ++numberOfLoops, --columnStart)
        {
            if (m_table[0][columnStart].m_playerFlag == playerMark)
            {
                for (int row{ 0 }; row < m_rows; ++row, --columnStart)
                {
                    if (m_table[row][columnStart].m_playerFlag == playerMark)
                    {
                        m_table[row][columnStart].reset();
                    }
                }
            }
        }
    }
}
//When looping to find the startPoint, it will only be valid if the playerMark found is from the starting column of each row
//ReverseWin: When looping to find the startPoint, it will only be valid if the playerMark found is from the ending column of each row
void Board::_clearDiagonalWinLopsidedColumn(const char playerMark, const bool reverseWin)
{
    int startPoint{};
    if (!reverseWin)
    {

    }
    else
    {

    }
}

bool Board::_multipleWinCases(const char playerMark) const
{
    int winCaseCount{};
    if (_isLateralWin(playerMark))
    {
        ++winCaseCount;
    }
    if (_isVerticalWin(playerMark))
    {
        ++winCaseCount;
    }
    //isDia does a lot of looping, only call if you have to.
    if (winCaseCount == 0)
    {
        return false;
    }
    else if (winCaseCount > 1)
    {
        return true;
    }
    if (_isDiagonalWin(playerMark))
    {
        ++winCaseCount;
    }
    return (winCaseCount > 1);
}
#endif