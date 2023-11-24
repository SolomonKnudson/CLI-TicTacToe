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

#ifdef BOARD_DEBUG
    //methods to set diff win conditions
    void setLateralWin(int row, int playerMark);
    void setVerticalWin(int column, int playerMark);
    void setDiagonalWin(int startPoint, int playerMark,
                        bool reverseWin = false);
    void setTie(int playerMark);

    void clearWinConfiguration(int playerMark);
private:
    struct ValidWinCases
    {
        std::vector<int> m_lateralCases{};
        std::vector<int> m_verticalCases{};
        std::vector<int> m_diagonalCases{}; 
    };

    //util methods for board debugging
    void _setDiagonalWinEvenBoard(int playerMark,
                                 bool reverseWin);
    void _setDiagonalWinLopsidedRow(int startColumn, int playerMark,
                                   bool reverseWin);
    void _setDiagonalWinLopsidedColumn(int startRow, int playerMark,
                                   bool reverseWin);

    bool _isValidWinCase(int startPoint, WinCase winCase,
                        bool reverseWin = false) const;

    static bool _isValidWin(const std::vector<int>& winCases,
                           int startPoint);
    static bool _isValidDiagonalWin(const std::vector<int>& winCases,
                            int startPoint,
                            bool reverseWin = false);

    std::vector<int> _validLateralWinCases() const;
    std::vector<int> _validVerticalWinCases() const;
    std::vector<int> _validDiagonalWinCases() const;

    //Util Mehods for clearWinConFig()
    void _clearLateralWin(int playerMark);
    void _clearVerticalWin(int playerMark);
    void _clearDiagonalWin(int playerMark);
    bool _multipleWinCases(int playerMark) const;

    //Util for clearDiaWin();
    void _clearDiagonalWinEvenBoard(bool reverseWin = false );
    void _clearDiagonalWinLopsidedRow(int playerMark, bool reverseWin = false);
    void _clearDiagonalWinLopsidedColumn(int playerMark, bool reverseWin = false);
    bool m_diagonalReverseWin{};
#else
private:
#endif //BOARD_DEBUG
    //Methods to help with display formatting
    //Positive ints only!
    static bool _isSingleDigit(int column);
    static bool _isDoubleDigit(int column);
    static bool _isTripleDigit(int column);
    void _dashLine() const;

    //Win subcases(Util methods for isWiningMove())
    bool _isLateralWin(int playerMark) const;
    bool _isVerticalWin(int playerMark) const;
    bool _isDiagonalWin(int playerMark) const;

    //Diagonal subcases(Util methods for _isDiaWin)
    bool _evenBoard(int playerMark) const;
    bool _lopsidedRow(int playerMark) const;
    bool _lopsidedColumn(int playerMark) const;

    //Member Vars
    Table m_table{};
    mutable WinCase m_winCase{};
    int m_rows{};
    int m_columns{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H

