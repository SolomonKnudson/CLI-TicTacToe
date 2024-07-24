#include "player.hpp"

//Constructors
Player::Player(const char mark, const std::string_view name)
  : m_moves{}
  , m_name{name}
  , m_wins{}
  , m_inValidMoves{}
  , m_mark{mark}
{
}

//Move Logic
int
Player::moves() const
{
  return static_cast<int>(m_moves.size());
}

bool
Player::isOccupying(const int move) const
{
  for (const auto& m_move : m_moves)
  {
    if (m_move == move)
    {
      return true;
    }
  }

  return false;
}

void
Player::addMove(const int move)
{
  m_moves.push_back(move);
}

void
Player::clearMoves()
{
  m_moves.clear();
}

//Invalid Move
int
Player::invalidMoves() const
{
  return m_inValidMoves;
}

void
Player::addInvalidMove()
{
  m_inValidMoves++;
}

void
Player::resetInvalidMoves()
{
  m_inValidMoves = 0;
}

//Mark Logic
int
Player::mark() const
{
  return m_mark;
}

void
Player::setMark(const int mark)
{
  m_mark = mark;
}

//Win Count Logic
int
Player::wins() const
{
  return m_wins;
}

void
Player::addWin()
{
  m_wins++;
}

void
Player::resetWins()
{
  m_wins = 0;
}

//Name Logic
std::string_view
Player::name() const
{
  return m_name;
}
