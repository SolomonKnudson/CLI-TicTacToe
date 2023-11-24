cmake_minimum_required(VERSION 3.14)

project(TicTacToeRepo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(TicTacToeRepo
  "src/main.cpp"
  "src/tictactoe.h"
  "src/tictactoe.cpp"
  "src/board.h"
  "src/board.cpp"
  "src/boardDebug.cpp"
  "src/player.h"
  "src/player.cpp"
)
