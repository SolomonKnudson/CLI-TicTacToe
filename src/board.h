#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string_view>
//TODO: implement clearDiaWin
//NOTE!: max board size that I can display is 63x63

//uncomment for automated win conditions
#define BOARD_DEBUG

class Board
{
    enum class WinCase
    {
        Lateral,
        Vertical,
        Diagonal,
        NoWinCase
    };
    using Table = std::vector<std::vector<int>>;
public:
    explicit Board(int row = 0, int column = 0);
    ~Board() = default;

    Board(const Board&) = delete;
    Board(const Board&&) = delete;

    Board& operator=(const Board&) = delete;
    Board& operator=(const Board&&) = delete;

    //Table Logic
    void display(int playerX, int playerO) const;
    void setBoard(int rows, int columns);
    void coverBoardSlot(int tablePosition, int currentPlayer);
    int boardSize() const;

    //Not in use
    int rows() const;
    int columns() const;
    //

    enum  BoardSize
    {
        standardRow = 3,
        standardColumn = 3,
        standardSize = standardRow * standardColumn,

        maxRow = 55,
        maxColumn = 55,
        maxSize = maxRow * maxColumn //55x55 hard cap  
    };

    //Win Logic
    //const for winningMove() is a lie; Object will change if true
    //(see m_winCase declaration).
    bool isWinningMove(int playerMark) const;
    bool isTie(int playerX, int playerO) const;

    //Util
    std::string_view winCase() const;
    void resetBoard();
    bool isEmpty() const;

    //Methods to help with display formatting
    //Positive ints only!
    static bool isSingleDigit(int column);
    static bool isDoubleDigit(int column);
    static bool isTripleDigit(int column);

#ifdef BOARD_DEBUG
    //methods to set diff win conditions
    void setLateralWin(int row, int playerMark);
    void setVerticalWin(int column, int playerMark);
    void setDiagonalWin(int startPoint, int playerMark,
                        bool reverseWin = false);
    void setTie(int playerMark);

    void clearWinConfiguration(int playerMark);
//private:
 //Public Just for testing!
public:
    struct ValidWinCases
    {
        std::vector<int> m_lateralCases{};
        std::vector<int> m_verticalCases{};
        std::vector<int> m_diagonalCases{}; 
    };

    //util methods for board debugging
    void setDiagonalWinEvenBoard(int playerMark,
                                 bool reverseWin);
    void setDiagonalWinLopsidedRow(int startColumn, int playerMark,
                                   bool reverseWin);
    void setDiagonalWinLopsidedColumn(int startRow, int playerMark,
                                   bool reverseWin);

    bool isValidWinCase(int startPoint, WinCase winCase,
                        bool reverseWin = false) const;

    static bool isValidWin(const std::vector<int>& winCases,
                           int startPoint);
    static bool isValidDiagonalWin(const std::vector<int>& winCases,
                            int startPoint,
                            bool reverseWin = false);

    std::vector<int> validLateralWinCases() const;
    std::vector<int> validVerticalWinCases() const;
    std::vector<int> validDiagonalWinCases() const;

    void clearLateralWin(int playerMark);
    void clearVerticalWin(int playerMark);
    void clearDiagonalWin(int playerMark);
    void clearDiagonalWinEvenBoard(bool reverseWin = false );
    void clearDiagonalWinLopsidedRow(int playerMark, bool reverseWin = false);
    void clearDiagonalWinLopsidedColumn(int playerMark, bool reverseWin = false);
    bool multipleWinCases(int playerMark) const;
    //Util bool for clearDiaWin();
    bool m_diagonalReverseWin{};
#else
private:
#endif //BOARD_DEBUG
    void dashLine() const;

    //Win subcases
    bool isLateralWin(int playerMark) const;
    bool isVerticalWin(int playerMark) const;
    bool isDiagonalWin(int playerMark) const;

    //Diagonal subcases
    bool evenBoard(int playerMark) const;
    bool lopsidedRow(int playerMark) const;
    bool lopsidedColumn(int playerMark) const;

    //Member Vars
    Table m_table{};
    mutable WinCase m_winCase{};
    int m_rows{};
    int m_columns{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H

