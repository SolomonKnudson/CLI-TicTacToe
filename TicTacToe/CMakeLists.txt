cmake_minimum_required(VERSION 3.15)

add_library(TicTacToe
	src/tictactoe.cpp
)

target_include_directories(TicTacToe PUBLIC include)

target_link_libraries(TicTacToe PRIVATE Board Player)