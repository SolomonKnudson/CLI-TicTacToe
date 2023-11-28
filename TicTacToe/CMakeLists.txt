cmake_minimum_required(VERSION 3.15)

add_library(TicTacToe
	${CMAKE_CURRENT_SOURCE_DIR}/src/tictactoe.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/tictactoeUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/tictactoeMoveLogic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/tictactoeGameLogic.cpp
)

target_include_directories(TicTacToe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_link_libraries(TicTacToe PUBLIC Board Player)
add_dependencies(TicTacToe Board Player)