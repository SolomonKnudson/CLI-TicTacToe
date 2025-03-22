cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(TicTacToeRepo LANGUAGES CXX)

add_library(TicTacToe)
add_library(CLI-TicTacToe::TicTacToe ALIAS TicTacToe)

target_sources(TicTacToe PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TicTacToe/tictactoe.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TicTacToe/tictactoeUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TicTacToe/tictactoeMoveLogic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TicTacToe/tictactoeGameLogic.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/player.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Board/boardTableLogic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Board/boardUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Board/isWinConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Board/debug/setWinConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Board/debug/clearWinConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Board/debug/isValidWinCase.cpp
)

target_include_directories(TicTacToe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(TicTacToe PUBLIC cxx_std_17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/App)
