#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>

class Player
{
    using Moves = std::vector<int>;
public:
    explicit Player(const int mark = 0, const std::string_view name = "");

    //Move Logic
    int moves() const;
    bool isOccupying(const int move) const;
    void addMove(const int move);
    void clearMoves();

    //Invalid Move
    int invalidMoves() const;
    void addInvalidMove();
    void resetInvalidMoves();

    //Mark Logic
    int mark() const;
    void setMark(const int mark);

    //Win Count Logic
    int wins() const;
    void addWin();
    void resetWins();

    //Name Logic
    std::string_view name() const;

    //Util
    //void setWins(int wins) { m_wins = wins; }
private:
    //Member Vars
    Moves m_moves{};
    std::string m_name{};
    int m_mark{};
    int m_wins{};
    int m_inValidMoves{};
};
#endif // PLAYER_H
