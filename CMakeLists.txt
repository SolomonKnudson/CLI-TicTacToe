cmake_minimum_required(VERSION 3.14)

project(TicTacToeRepo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(TicTacToeRepo
  "Src/main.cpp"
  "Src/tictactoe.h"
  "Src/tictactoe.cpp"
  "Src/board.h"
  "Src/board.cpp"
  "Src/boardDebug.cpp"
  "Src/player.h"
  "Src/player.cpp"
)
