#ifndef CLI_TICTACTOE_PLAYER_H
#define CLI_TICTACTOE_PLAYER_H
#include <string>
#include <string_view>
#include <unordered_set>

class Player
{
  using Moves = std::unordered_set<int>;

public:
  explicit Player(char mark = ' ', std::string_view name = "");

  //Move Logic
  int
  moves() const;

  bool
  isOccupying(int move) const;

  void
  addMove(int move);

  void
  clearMoves();

  //Invalid Move
  int
  invalidMoves() const;

  void
  addInvalidMove();

  void
  resetInvalidMoves();

  //Mark Logic
  char
  mark() const;

  void
  setMark(char mark);

  //Win Count Logic
  int
  wins() const;

  void
  addWin();

  void
  resetWins();

  //Name Logic
  std::string_view
  name() const;

private:
  //Member Vars
  Moves m_moves{};
  std::string m_name{};
  int m_wins{};
  int m_inValidMoves{};
  char m_mark{};
};
#endif // CLI_TICTACTOE_PLAYER_H
