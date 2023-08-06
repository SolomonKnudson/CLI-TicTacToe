#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
#include <vector>
#include <limits>
#include "board.h"
#include "player.h"

class TicTacToe
{
    struct MatchRecord
    {
        std::string_view m_winner{};
        std::string_view m_winCase{};
        int m_matchID{};
        int m_row{};
        int m_column{};
        int m_moves{};
        bool m_tieGame{};
    };
    using MatchRecords = std::vector<MatchRecord>;
public:
    TicTacToe();
    ~TicTacToe() = default;

    TicTacToe(const TicTacToe&) = delete;
    TicTacToe(const TicTacToe&&) = delete;

    TicTacToe& operator=(const TicTacToe&) = delete;
    TicTacToe& operator=(const TicTacToe&&) = delete;
private:
    //setup Logic
    void setupGame();
    void setBoard();

    //Board Logic
    void displayBoard() const;

    //Game logic
    void gameLoop();
    void endGame();
    void resetGame();

    //Move Logic
    void getMove();
    void move();
    bool isLegalMove() const;
    bool isValidPosition() const;

    //Win Logic
    bool isWinningMove() const;
    bool isTieGame() const;

    //Player Logic
    void displayStats() const;
    void nextPlayer();
    Player& currentPlayer();

    //Util Methods
    void flushCin() const;
    void checkBoardSize();
    void displayBoardConfiguration() const;
    void createMatchRecord();
    void displayMatchRecords() const;
    void quit() const;
private:
    Board m_board{};

    Player m_playerX{};
    Player m_playerO{};

    MatchRecords m_matchRecords{};

    int m_previousRow{};
    int m_previousColumn{};
    int m_tablePosition{};

    int m_firstPlayer{};
    int m_currentPlayerMark{};
    int m_totalInvalidMovesAllowed{};

    int m_tieGames{};
    bool m_hasWon{};
    bool m_tie{};

    bool m_isFirstGame{};
};
#endif // TICTACTOE_H
