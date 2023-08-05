#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string_view>

//NOTE!: max board size that I can display is 63x63
//TODO: Implement setDiagonalWin()|prolly won't be do, tbh|

//uncomment for automated win conditions
//#define BOARDDEBUG

class Board
{
    enum class WinCase
    {
        Lateral,
        Vertical,
        Diagonal
    };
    using Table = std::vector<std::vector<int>>;
public:
    explicit Board(const int row = 0, const int colum = 0);
    ~Board() = default;

    Board(const Board&) = delete;
    Board(const Board&&) = delete;

    Board& operator=(const Board&) = delete;
    Board& operator=(const Board&&) = delete;
public:
    //Table Logic
    void display(const int playerX, const int playerO) const;
    void setBoard(const int rows, const int colums);
    void coverBoardSlot(const int tablePosition, const int currentPlayer);
    int boardSize() const;

    //Not in use
    int rows() const;
    int colums() const;
    //

    static constexpr int maxRow{11};
    static constexpr int maxColum{15};
    static constexpr int maxSize{maxRow * maxColum};//11x15 soft cap

    static constexpr int standardRow{3};
    static constexpr int standardColum{3};
    static constexpr int standardSize{standardRow * standardColum};

    //Win Logic
    //const for winningMove() is a lie; Object will change if true
    //(see m_winCase declaration).
    bool isWinningMove(const int playerMark) const;
    bool isTie(const int playerX, const int playerO) const;

    //Util
    std::string_view winCase() const;
    void resetBoard();

    //methods to set diff win conditions
#ifdef BOARDDEBUG
    void setLateralWin(const int row, const int playerMark);
    void setVerticalWin(const int colum, const int playerMark);
//    void setDiagonalWin(const int colum, const int playerMark,
//                        const bool reverseCase = false);//Not implemented yet
    void setTie(const int playerMark);
#endif
    //Methods to help with display formatting
    //Positive ints only!
    static bool isSingleDigit(const int colum);
    static bool isDoubleDigit(const int colum);
    static bool isTripleDigit(const int colum);
private:
    void dashLine() const;

    //Win subcases
    bool isLateralWin(const int playerMark) const;
    bool isVerticalWin(const int playerMark) const;
    bool isDiagonalWin(const int playerMark) const;

    //Diagonal subcases
    bool evenBoard(const int playerMark) const;
    bool lopSidedRow(const int playerMark) const;
    bool lopSidedColum(const int playerMark) const;
private:
    Table m_table{};
    mutable WinCase m_winCase{};
    int m_rows{};
    int m_colums{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H

