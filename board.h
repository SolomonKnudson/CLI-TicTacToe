#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string_view>

//NOTE!: max board size that I can display is 63x63

//uncomment for automated win conditions
#define BOARDDEBUG

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

    static constexpr int maxRow{11};
    static constexpr int maxColumn{15};
    static constexpr int maxSize{maxRow * maxColumn};//11x15 soft cap

    static constexpr int standardRow{3};
    static constexpr int standardColumn{3};
    static constexpr int standardSize{standardRow * standardColumn};

    //Win Logic
    //const for winningMove() is a lie; Object will change if true
    //(see m_winCase declaration).
    bool isWinningMove(const int playerMark) const;
    bool isTie(const int playerX, const int playerO) const;

    //Util
    std::string_view winCase() const;
    void resetBoard();

    //Methods to help with display formatting
    //Positive ints only!
    static bool isSingleDigit(const int column);
    static bool isDoubleDigit(const int column);
    static bool isTripleDigit(const int column);

    //methods to set diff win conditions
#ifdef BOARDDEBUG
    void setLateralWin(const int row, const int playerMark);
    void setVerticalWin(const int column, const int playerMark);
    void setDiagonalWin(int startColumn, const int playerMark,
                        const bool reverseCase = false);
    void setTie(const int playerMark);

private:
    struct ValidWinCases
    {
        std::vector<int> m_lateralCases{};
        std::vector<int> m_verticalCases{};
        std::vector<int> m_diagonalCases{};
    };

    //util methods for board debugging
    void setDiagonalWinEvenBoard(const int playerMark,
                                 const bool reverseCase);
    void setDiagonalWinLopSidedRow(int startColumn, const int playerMark,
                                   const bool reverseCase);
    void setDiagonalWinLopSidedColumn(int startColumn, const int playerMark,
                                   const bool reverseCase);

    bool isValidWinCase(int startPoint, WinCase winCase,
                        bool reverseCase = false) const;

    bool isValidWin(const std::vector<int>& winCases,
                           const int startPoint) const;
    bool isValidDiagonalWin(const std::vector<int>& winCases,
                            const int startPoint,
                            const bool reverseCase = false) const;

    const std::vector<int> validLateralWinCases() const;
    const std::vector<int> validVerticalWinCases() const;
    const std::vector<int> validDiagonalWinCases() const;
#else
private:
#endif
    void dashLine() const;

    //Win subcases
    bool isLateralWin(const int playerMark) const;
    bool isVerticalWin(const int playerMark) const;
    bool isDiagonalWin(const int playerMark) const;

    //Diagonal subcases
    bool evenBoard(const int playerMark) const;
    bool lopSidedRow(const int playerMark) const;
    bool lopSidedColumn(const int playerMark) const;

    Table m_table{};
    mutable WinCase m_winCase{};
    int m_rows{};
    int m_columns{};
    int m_boardSize{};
    bool m_evenBoard{};
};
#endif // BOARD_H
