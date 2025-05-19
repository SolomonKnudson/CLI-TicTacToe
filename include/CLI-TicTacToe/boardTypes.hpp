#ifndef CLI_TICTACTOE_BOARD_TYPES_H
#define CLI_TICTACTOE_BOARD_TYPES_H
#include <vector>

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
    maxSize = maxRow * maxColumn
  };

  enum class WinCase
  {
    Lateral,
    Vertical,

    Diagonal,
    NoWinCase
  };
} // namespace BoardTypes
#endif // CLI_TICTACTOE_BOARD_TYPES_H
