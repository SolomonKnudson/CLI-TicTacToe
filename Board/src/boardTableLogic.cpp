#include <iostream>
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
            if (column.m_piecePosition == tablePosition && !column.m_playerIsOccupying)
            {
                column.m_playerFlag = currentPlayer;
                column.m_playerIsOccupying = true;
                return;
            }
        }
    }
}