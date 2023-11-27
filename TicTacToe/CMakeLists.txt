cmake_minimum_required(VERSION 3.15)

add_library(TicTacToe
	${CMAKE_CURRENT_SOURCE_DIR}/src/tictactoe.cpp
)

target_include_directories(TicTacToe PUBLIC include)


target_link_libraries(TicTacToe PUBLIC Board Player)
add_dependencies(TicTacToe Board Player)