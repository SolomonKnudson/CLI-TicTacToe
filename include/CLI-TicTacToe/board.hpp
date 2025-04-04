#ifndef CLI_TICTACTOE_BOARD_H
#define CLI_TICTACTOE_BOARD_H
#include <string_view>
#include <vector>

//NOTE!: max board size that I can display is 50x50

//uncomment for automated win conditions
#define BOARD_DEBUG

namespace BoardTypes
{
  struct BoardPiece
  {
    void
    reset()
    {
      m_playerFlag = ' ';
      m_playerIsOccupying = false;
    }

    explicit BoardPiece(int piecePosition, char playerFlag = ' ')
      : m_piecePosition{piecePosition}
      , m_playerFlag{playerFlag}
      , m_playerIsOccupying{false}
    {
    }

    int m_piecePosition{};
    char m_playerFlag{};
    bool m_playerIsOccupying{};
  };

  using Table = std::vector<std::vector<BoardPiece>>;

  enum BoardSize
  {
    standardRow = 3,
    standardColumn = 3,
    standardSize = standardRow * standardColumn,

    maxRow = 50,
    maxColumn = 50,
    maxSize = maxRow * maxColumn //50x50 hard cap.(changed cmds)
  };

  enum class WinCase
  {
    Lateral,
    Vertical,

    Diagonal,
    NoWinCase
  };
} // namespace BoardTypes

class Board
{
public:
  explicit Board(int row = 3, int column = 3);
  ~Board() = default;

  Board(const Board&) = delete;
  Board(const Board&&) = delete;

  Board&
  operator=(const Board&) = delete;

  Board&
  operator=(const Board&&) = delete;

  //Table Logic
  void
  display() const;

  void
  setBoard(int rows, int columns);

  void
  coverBoardSlot(int tablePosition, char currentPlayer);

  int
  boardSize() const;

  //Not in use
  int
  rows() const;

  int
  columns() const;

  //Win Logic
  //const for winningMove() is a lie; Object will change if true
  //(see m_winCase declaration).
  bool
  isWinningMove(char playerMark) const;

  bool
  isTie() const;

  //Util
  std::string_view
  winCase() const;

  bool
  isEmpty() const;

  bool
  isEvenBoard() const;

  const BoardTypes::Table&
  internalTable() const;

  void
  resetBoard();

#ifdef BOARD_DEBUG
  //methods to set diff win conditions
  bool
  setLateralWin(int row, char playerMark);

  bool
  setVerticalWin(int column, char playerMark);

  bool
  setDiagonalWin(int startPoint, char playerMark, bool reverseWin = false);

  bool
  setTie(char playerMark);

  void
  clearWinConfiguration(char playerMark);

private:
  struct ValidWinCases
  {
    std::vector<int> m_lateralCases{};
    std::vector<int> m_verticalCases{};
    std::vector<int> m_diagonalCases{};
  };

  //util methods for board debugging
  void
  _setDiagonalWinEvenBoard(char playerMark, bool reverseWin);

  void
  _setDiagonalWinLopsidedRow(int startColumn, char playerMark, bool reverseWin);

  void
  _setDiagonalWinLopsidedColumn(int startRow, char playerMark, bool reverseWin);

  bool
  _isValidWinCase(int startPoint,
                  BoardTypes::WinCase winCase,
                  bool reverseWin = false);

  static bool
  _isValidWin(const std::vector<int>& winCases, int startPoint);

  static bool
  _isValidDiagonalWin(const std::vector<int>& winCases,
                      int startPoint,
                      bool reverseWin = false);

  //Util methods for isValidWinCase()
  void
  _recalculateWinCases(ValidWinCases& winCases);

  std::vector<int>
  _validLateralWinCases() const;

  std::vector<int>
  _validVerticalWinCases() const;

  std::vector<int>
  _validDiagonalWinCases() const;

  //Util mehods for clearWinConFig()
  void
  _clearLateralWin(char playerMark);

  void
  _clearVerticalWin(char playerMark);

  void
  _clearDiagonalWin(char playerMark);

  //Util for clearDiaWin();
  void
  _clearDiagonalWinEvenBoard(char playerMark);

  void
  _clearDiagonalWinLopsidedRow(char playerMark);

  void
  _clearDiagonalWinLopsidedColumn(char playerMark);

  bool
  _multipleWinCases(char playerMark) const;

  bool m_diagonalReverseWin{};
#else
private:
#endif //BOARD_DEBUG
  //Methods to help with display formatting
  //Positive ints only!
  static bool
  _isSingleDigit(int column);

  static bool
  _isDoubleDigit(int column);

  static bool
  _isTripleDigit(int column);

  void
  _dashLine() const;

  //Win subcases(Util methods for isWiningMove())
  bool
  _isLateralWin(char playerMark) const;

  bool
  _isVerticalWin(char playerMark) const;

  bool
  _isDiagonalWin(char playerMark) const;

  //Diagonal subcases(Util methods for _isDiaWin)
  bool
  _isDiagonalWinEvenBoard(char playerMark) const;

  bool
  _isDiagonalWinLopsidedRow(char playerMark) const;

  bool
  _isDiagonalWinLopsidedColumn(char playerMark) const;

  //Member Vars
  BoardTypes::Table m_table{};
  mutable BoardTypes::WinCase m_winCase{};
  int m_rows{};
  int m_columns{};
  int m_boardSize{};
  bool m_evenBoard{};
};
#endif // CLI_TICTACTOE_BOARD_H
