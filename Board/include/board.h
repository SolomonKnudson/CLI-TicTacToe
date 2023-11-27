#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string_view>
//TODO: implement clearDiaWin
//NOTE!: max board size that I can display is 63x63

//uncomment for automated win conditions
#define BOARD_DEBUG

namespace BoardTypes
{
    struct BoardPiece
    {
        void reset()
        {
            m_playerFlag = ' ';
            m_playerIsOccupying = false;
        }
        BoardPiece(int piecePosition, char playerFlag = ' ')
            : m_piecePosition{ piecePosition }
            , m_playerFlag{ playerFlag }
            , m_playerIsOccupying{ false }
        {}
        int m_piecePosition{};
        char m_playerFlag{};
        bool m_playerIsOccupying{};
    };

    enum  BoardSize
    {
        standardRow = 3,
        standardColumn = 3,
        standardSize = standardRow * standardColumn,

        maxRow = 55,
        maxColumn = 55,
        maxSize = maxRow * maxColumn //55x55 hard cap  
    };

    enum class WinCase
    {
        Lateral,
        Vertical,
        Diagonal,
        NoWinCase
    };
}

class Board
{
    using Table = std::vector<std::vector<BoardTypes::BoardPiece>>;
public:
    explicit Board(int row = 3, int column = 3);
    ~Board() = default;

    Board(const Board&) = delete;
    Board(const Board&&) = delete;

    Board& operator=(const Board&) = delete;
    Board& operator=(const Board&&) = delete;

    //Table Logic
    void display() const;
    void setBoard(int rows, int columns);
    void coverBoardSlot(int tablePosition, char currentPlayer);
    int boardSize() const;

    //Not in use
    int rows() const;
    int columns() const;

    //Win Logic
    //const for winningMove() is a lie; Object will change if true
    //(see m_winCase declaration).
    bool isWinningMove(char playerMark) const;
    bool isTie() const;

    //Util
    std::string_view winCase() const;
    void resetBoard();
    bool isEmpty() const;

#ifdef BOARD_DEBUG
    //methods to set diff win conditions
    bool setLateralWin(int row, char playerMark);
    bool setVerticalWin(int column, char playerMark);
    bool setDiagonalWin(int startPoint, char playerMark,
                        bool reverseWin = false);
    bool setTie(char playerMark);

    void clearWinConfiguration(char playerMark);
private:
    struct ValidWinCases
    {
        std::vector<int> m_lateralCases{};
        std::vector<int> m_verticalCases{};
        std::vector<int> m_diagonalCases{}; 
    };

    //util methods for board debugging
    void _setDiagonalWinEvenBoard(char playerMark,
                                 bool reverseWin);
    void _setDiagonalWinLopsidedRow(int startColumn, char playerMark,
                                   bool reverseWin);
    void _setDiagonalWinLopsidedColumn(int startRow, char playerMark,
                                   bool reverseWin);

    bool _isValidWinCase(int startPoint, BoardTypes::WinCase winCase,
                        bool reverseWin = false);

    static bool _isValidWin(const std::vector<int>& winCases,
                           int startPoint);
    void _recalculateWinCases(ValidWinCases& winCases);
    static bool _isValidDiagonalWin(const std::vector<int>& winCases,
                            int startPoint,
                            bool reverseWin = false);

    std::vector<int> _validLateralWinCases() const;
    std::vector<int> _validVerticalWinCases() const;
    std::vector<int> _validDiagonalWinCases() const;

    //Util Mehods for clearWinConFig()
    void _clearLateralWin(char playerMark);
    void _clearVerticalWin(char playerMark);
    void _clearDiagonalWin(char playerMark);
    bool _multipleWinCases(char playerMark) const;

    //Util for clearDiaWin();
    void _clearDiagonalWinEvenBoard(bool reverseWin = false );
    void _clearDiagonalWinLopsidedRow(char playerMark, bool reverseWin = false);
    void _clearDiagonalWinLopsidedColumn(char playerMark, bool reverseWin = false);
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
    bool _isLateralWin(char playerMark) const;
    bool _isVerticalWin(char playerMark) const;
    bool _isDiagonalWin(char playerMark) const;

    //Diagonal subcases(Util methods for _isDiaWin)
    bool _evenBoard(char playerMark) const;
    bool _lopsidedRow(char playerMark) const;
    bool _lopsidedColumn(char playerMark) const;

    //Member Vars
    Table m_table{};
    mutable BoardTypes::WinCase m_winCase{};
    int m_rows{};
    int m_columns{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H

