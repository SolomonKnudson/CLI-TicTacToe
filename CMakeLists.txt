cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

project(CLI-TicTacToe LANGUAGES CXX)

add_library(TicTacToe)
add_library(CLI-TicTacToe::TicTacToe ALIAS TicTacToe)

target_sources(TicTacToe PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}/src/TicTacToe/tictactoe.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/TicTacToe/tictactoeUtil.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/TicTacToe/tictactoeMoveLogic.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/TicTacToe/tictactoeGameLogic.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/player.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/Board/boardTableLogic.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Board/boardUtil.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Board/isWinConfig.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Board/debug/setWinConfig.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Board/debug/clearWinConfig.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Board/debug/isValidWinCase.cpp
)

target_include_directories(TicTacToe 
  PUBLIC  $<BUILD_LOCAL_INTERFACE: ${CMAKE_CURRENT_LIST_DIR}/include>
  PRIVATE $<BUILD_LOCAL_INTERFACE: ${CMAKE_CURRENT_LIST_DIR}/src/Board/debug>
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/App)
