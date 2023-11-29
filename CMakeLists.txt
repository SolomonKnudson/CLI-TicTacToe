cmake_minimum_required(VERSION 3.14)

project(TicTacToeRepo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(CLI-TicTacToe
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)


target_link_libraries(CLI-TicTacToe PUBLIC TicTacToe)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TicTacToe)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Board)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Player)
