cmake_minimum_required(VERSION 3.14)

project(TicTacToeRepo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(TicTacToeRepo
  main.cpp
  tictactoe.h
  tictactoe.cpp
  board.h
  board.cpp
  player.h
  player.cpp
)
