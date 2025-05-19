#ifndef CLI_TICTACTOE_BOARD_H
#define CLI_TICTACTOE_BOARD_H
#include <CLI-TicTacToe/boardTypes.hpp>
#include <string_view>
#include <vector>

//uncomment for automated win conditions
//#define BOARD_DEBUG

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

  //Win subcases(Util methods for isWiningMove())
  bool
  isLateralWin(char playerMark) const;

  bool
  isVerticalWin(char playerMark) const;

  bool
  isDiagonalWin(char playerMark) const;

  bool
  isTie() const;

  //Util
  std::string_view
  winCaseToString() const;

  BoardTypes::WinCase
  winCase() const;

  bool
  isEmpty() const;

  bool
  isEvenBoard() const;

  const BoardTypes::Table&
  cInternalTable() const;

  BoardTypes::Table&
  internalTable();

  void
  resetBoard();

private:
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
