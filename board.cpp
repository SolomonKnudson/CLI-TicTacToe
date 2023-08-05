#include "board.h"

//Constructors
Board::Board(const int row, const int colum)
    : m_table{}
    , m_winCase{}
    , m_rows{}
    , m_colums{}
    , m_boardSize{}
    , m_evenBoard{}
{
    if(row >= 3 && colum >= 3)
    {
        this -> setBoard(row, colum);
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
        for(const auto& colum : row)
        {
            if(colum == playerX)
            {
                std::cout << " X  |";
//                std::cout << " " << colum << " |";
            }
            else if(colum == playerO)
            {
                std::cout << " O  |";
//                std::cout << " " << colum << " |";
            }
            else
            {//  |1   |2   |3   |
                if(this -> isSingleDigit(colum))
                {
                    std::cout << " " << colum << "  |";
                }//  |14  |15  |16  |
                else if(this -> isDoubleDigit(colum))
                {
                    std::cout << " " << colum << " |";
                }//|700 |800 |900 |
                else if(this -> isTripleDigit(colum))
                {
                    std::cout << " " << colum << "|";
                }//1000|2000|3000
                else
                {
                    std::cout << colum << "|";
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

int Board::colums() const
{
    return m_colums;
}

int Board::boardSize() const
{
    return m_boardSize;
}

void Board::setBoard(int rows, int colums)
{
    m_rows = rows;
    m_colums = colums;
    m_boardSize = m_rows * m_colums;

    if(m_rows == m_colums)
    {
        m_evenBoard = true;
    }

    for(int row{0}; row < m_rows; row++)
    {
        m_table.push_back(std::vector<int>{});
    }

    int colum{1};

    for(auto& row : m_table)
    {
        for(int i{0}; i < m_colums; i++)
        {
            row.push_back(colum++);
        }
    }

}

void Board::coverBoardSlot(const int tablePosition, const int currentPlayer)
{
    for(auto& row : m_table)
    {
        for(auto& colum : row)
        {
            if(colum == tablePosition)
            {
                colum = currentPlayer;
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
        for(const auto& colum : row)
        {
            if(colum == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_colums)
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
    for(int colum{0}; colum < m_colums; colum++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row][colum] == playerMark)
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
    else if(m_rows < m_colums)
    {
        return this -> lopSidedRow(playerMark);
    }
    else if (m_colums < m_rows)
    {
        return this -> lopSidedColum(playerMark);
    }
    return false;
}

//Diagonal subcases
bool Board::evenBoard(const int playerMark) const
{
    int inARow{};
    for(int row{0}, colum{0}; row < m_rows; row++, colum++)
    {
        if(m_table[row][colum] == playerMark)
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
    for(int row{0}, columOffSet{m_colums - 1}; row < m_rows; row++)
    {
        if(m_table[row].at(columOffSet - row) == playerMark)
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
    *NOTE: if rows < colums, colums - rows = only diagonal cases(Colum Based)
    *ex. 4x8: Diagona cases: colum: 0, 1, 2, 3, 4 index based!
    *10x11: Diagona cases: colum: 0, 1
    *
*/
bool Board::lopSidedRow(const int playerMark) const
{
    int inARow{};
    int offSet{m_colums -  m_rows};
    for(int colum{0}; colum <= offSet; colum++)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(colum + row) == playerMark)
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
    for(int colum{m_colums - 1}; colum >= ((m_colums - 1) - offSet); colum--)
    {
        for(int row{0}; row < m_rows; row++)
        {
            if(m_table[row].at(colum - row) == playerMark)
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
    *NOTE: if colums < rows, rows -  colums = only diagonal cases(Row Based);
    *must account for a 'lower' row diagonal win
    *ex. 8x4: Diagona cases: row: 0, 1, 2, 3, 4 index based!
    *15x11: Diagona cases: row: 0, 1, 2, 3, 4
*/
bool Board::lopSidedColum(const int playerMark) const
{
    int inARow{};
    int offSet{m_rows -  m_colums};
    for(int loop{0}; loop <= offSet; loop++)
    {
        for(int row{0}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(loop + row).at(row) == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_colums)
        {
            return true;
        }
        inARow = 0;
    }
    inARow = 0;

    //Reverse case
    for(int loop{0}; loop <= offSet; loop++)
    {
        for(int row{0}, colum{m_colums - 1}; row < (m_rows - offSet); row++)
        {
            if(m_table.at(row + loop).at(colum - row) == playerMark)
            {
                inARow++;
            }
        }
        if(inARow == m_colums)
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
        for(const auto& colum : row)
        {
            if(colum == playerX || colum == playerO)
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
    m_colums = 0;
    if(m_evenBoard)
    {
        m_evenBoard = false;
    }
}

#ifdef BOARDDEBUG
//methods to set diff win conditions
void Board::setLateralWin(const int row, const int playerMark)
{
    for(int fill{row}, endColum{row + m_colums}; fill < endColum; fill++)
    {
        this -> coverBoardSlot(fill, playerMark);
    }
}

/*
    * NOTE: if rows < colums, colums - rows + 1 = only diagonal cases
    * (Non-index, colum based)
    * colum + (m_colums + 1) = next colum to set for a diagonal win
    * ex. 4x8 Diagona cases: colum: 1, 10, 19, 28,
    * 10x11 Diaginal cases: colun:
*/
//NOTE: not in use
//void Board::setDiagonalWin(const int colum, const int playerMark,
//                           const bool reverseCase)
//{
//    if(m_evenBoard)
//    {
//        //Reverse case
//    }
//    else if(m_rows < m_colums)
//    {

//        //Reverse case
//    }
//    else if (m_colums < m_rows)
//    {

//        //Reverse case
//    }
//}

void Board::setVerticalWin(const int colum, const int playerMark)
{
    for(int row{0}, columOffset{colum}; row < m_rows;
        row++, columOffset += m_colums)
    {
        this -> coverBoardSlot(columOffset, playerMark);
    }
}

void Board::setTie(const int playerMark)
{
    for(int fill{1}; fill <= m_boardSize; fill++)
    {
        this -> coverBoardSlot(fill, playerMark);
    }
}
#endif
//Private Methods

//Methods to help with display formatting
//Positive ints only!
bool Board::isSingleDigit(const int colum)
{
    return colum < 10;
}

bool Board::isDoubleDigit(const int colum)
{
    return colum >= 10 && colum < 100;
}

bool Board::isTripleDigit(const int colum)
{
    return colum >= 100 && colum < 1000;
}

void Board::dashLine() const
{
    for(int dashLine{0}; dashLine < m_colums; dashLine++)
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
