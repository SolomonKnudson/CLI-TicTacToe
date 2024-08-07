#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

class Player
{
  using Moves = std::vector<int>;

public:
  explicit Player(char mark = ' ', std::string_view name = "");
  ~Player() = default;

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
  int
  mark() const;

  void
  setMark(int mark);

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

  //Util
  //void setWins(int wins) { m_wins = wins; }
private:
  //Member Vars
  Moves m_moves{};
  std::string m_name{};
  int m_wins{};
  int m_inValidMoves{};
  char m_mark{};
};
#endif // PLAYER_H
