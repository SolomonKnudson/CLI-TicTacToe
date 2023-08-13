#include "player.h"

//Constructors
Player::Player(const int mark, const std::string_view name)
    : m_moves{}
    , m_name{name}
    , m_mark{mark}
    , m_wins{}
    , m_inValidMoves{}
{}


//Move Logic
int Player::moves() const
{
    return m_moves.size();
}

bool Player::inMoves(const int move) const
{
    for(const auto& m_move : m_moves)
    {
        if(m_move == move)
        {
            return true;
        }
    }
    return false;
}

void Player::addMove(const int move)
{
    m_moves.push_back(move);
}

void Player::clearMoves()
{
    m_moves.clear();
}

//Invalid Move
int Player::inValidMoves() const
{
    return m_inValidMoves;
}

void Player::addInValidMove()
{
    m_inValidMoves++;
}

void Player::resetInValidMoves()
{
    m_inValidMoves = 0;
}

//Mark Logic
int Player::mark() const
{
    return m_mark;
}

void Player::setMark(const int mark)
{
    m_mark = mark;
}

//Win Count Logic
int Player::wins() const
{
    return m_wins;
}

void Player::addWin()
{
    m_wins++;
}

void Player::resetWins()
{
    m_wins = 0;
}

//Name Logic
std::string_view Player::name() const
{
    return m_name;
}

