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
    explicit Board(const int row = 0, const int column = 0);
    ~Board() = default;

    Board(const Board&) = delete;
    Board(const Board&&) = delete;

    Board& operator=(const Board&) = delete;
    Board& operator=(const Board&&) = delete;

    //Table Logic
    void display(const int playerX, const int playerO) const;
    void setBoard(const int rows, const int columns);
    void coverBoardSlot(const int tablePosition, const int currentPlayer);
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
    bool isWinningMove(const int playerMark) const;
    bool isTie(const int playerX, const int playerO) const;

    //Util
    std::string_view winCase() const;
    void resetBoard();
    bool isEmpty() const;

    //Methods to help with display formatting
    //Positive ints only!
    static bool isSingleDigit(const int column);
    static bool isDoubleDigit(const int column);
    static bool isTripleDigit(const int column);

#ifdef BOARD_DEBUG
    //methods to set diff win conditions
    void setLateralWin(const int row, const int playerMark);
    void setVerticalWin(const int column, const int playerMark);
    void setDiagonalWin(int startPoint, const int playerMark,
                        const bool reverseWin = false);
    void setTie(const int playerMark);

    void clearWinConfiguration(const int playerMark);
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
    void setDiagonalWinEvenBoard(const int playerMark,
                                 const bool reverseWin);
    void setDiagonalWinLopsidedRow(int startColumn, const int playerMark,
                                   const bool reverseWin);
    void setDiagonalWinLopsidedColumn(int startRow, const int playerMark,
                                   const bool reverseWin);

    bool isValidWinCase(const int startPoint, const WinCase winCase,
                        const bool reverseWin = false) const;

    bool isValidWin(const std::vector<int>& winCases,
                           const int startPoint) const;
    bool isValidDiagonalWin(const std::vector<int>& winCases,
                            const int startPoint,
                            const bool reverseWin = false) const;

    const std::vector<int> validLateralWinCases() const;
    const std::vector<int> validVerticalWinCases() const;
    const std::vector<int> validDiagonalWinCases() const;

    void clearLateralWin(const int playerMark);
    void clearVerticalWin(const int playerMark);
    void clearDiagonalWin(const int playerMark);
    void clearDiagonalWinEvenBoard(const int playerMark, const bool reverseWin = false );
    void clearDiagonalWinLopsidedRow(const int playerMark, const bool reverseWin = false);
    void clearDiagonalWinLopsidedColumn(const int playerMark, const bool reverseWin = false);
    bool multipleWinCases(const int playerMark) const;
    //Util bool for clearDiaWin();
    bool m_diagonalReverseWin{};
#else
private:
#endif //BOARD_DEBUG
    void dashLine() const;

    //Win subcases
    bool isLateralWin(const int playerMark) const;
    bool isVerticalWin(const int playerMark) const;
    bool isDiagonalWin(const int playerMark) const;

    //Diagonal subcases
    bool evenBoard(const int playerMark) const;
    bool lopsidedRow(const int playerMark) const;
    bool lopsidedColumn(const int playerMark) const;

    //Member Vars
    Table m_table{};
    mutable WinCase m_winCase{};
    int m_rows{};
    int m_columns{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H

