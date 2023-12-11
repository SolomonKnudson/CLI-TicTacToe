#include "board.h"

#ifdef BOARD_DEBUG
using namespace BoardTypes;

//Util methods for all win case set'ers
bool Board::_isValidWinCase(const int startPoint, const WinCase winCase,
    const bool reverseWin)
{
    //Static so win cases aren't re-calculated unless using a different size board
    static ValidWinCases winCases
    {
        _validLateralWinCases(),
        _validVerticalWinCases(),
        _validDiagonalWinCases()
    };

    static int previousRow{ m_rows };
    static int previousColumn{ m_columns };

    if (previousRow != m_rows && previousColumn != m_columns)
    {
        previousRow = m_rows;
        previousColumn = m_columns;
        _recalculateWinCases(winCases);
    }

    switch (winCase)
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
void Board::_recalculateWinCases(ValidWinCases& winCases)
{
    winCases.m_lateralCases.clear();
    winCases.m_verticalCases.clear();
    winCases.m_diagonalCases.clear();

    //Have to do this as you cannot assign a vector to an already made vector
    for (int winCase : _validLateralWinCases())
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

bool Board::_isValidWin(const std::vector<int>& winCases,
    const int startPoint)
{
    for (const int winCase : winCases)
    {
        if (winCase == startPoint)
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
    const static int n{ static_cast<int>(winCases.size()) };
    const static int offSet{ n / 2 };

    if (!reverseWin)
    {
        for (int i{ 0 }; i < offSet; ++i)
        {
            if (winCases[i] == startPoint)
            {
                return true;
            }
        }
    }
    //reverse cases will always be the last [offset] number of elements in vec
    // offset to vec size
    else
    {
        for (int i{ offSet }; i < n; ++i)
        {
            if (winCases[i] == startPoint)
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

    for (int row{ 0 }; row < m_rows; ++row)
    {
        winCases.push_back(m_table[row][0].m_piecePosition);
    }

    return winCases;
}

std::vector<int> Board::_validVerticalWinCases() const
{
    std::vector<int> winCases{};

    for (int column{ 0 }; column < m_columns; ++column)
    {
        winCases.push_back(m_table[0][column].m_piecePosition);
    }

    return winCases;
}

std::vector<int> Board::_validDiagonalWinCases() const
{
    std::vector<int> winCases{};
    int offSet{};

    if (m_rows < m_columns)
    {
        offSet = m_columns - m_rows;
        for (int i{ 0 }; i <= offSet; ++i)
        {
            winCases.push_back(m_table[0][i].m_piecePosition);
        }

        //reverse cases
        for (int i{ 0 }; i <= offSet; ++i)
        {
            winCases.push_back(m_table[0]
                .at(static_cast<size_t>((m_columns - 1) - i)).m_piecePosition);
        }
    }
    else if (m_columns < m_rows)
    {
        offSet = m_rows - m_columns;
        for (int i{ 0 }; i <= offSet; ++i)
        {
            winCases.push_back(m_table[i][0].m_piecePosition);
        }

        //reverseWins
        for (int i{ 0 }; i <= offSet; ++i)
        {
            winCases.push_back(m_table[i][static_cast<size_t>(m_columns - 1)]
                .m_piecePosition);
        }
    }

    return winCases;
}
#endif //BOARD_DEBUG