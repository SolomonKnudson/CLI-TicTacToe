cmake_minimum_required(VERSION 3.14)

project(TicTacToeRepo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(TicTacToeRepo
  "src/main.cpp"
)


target_link_libraries(TicTacToeRepo PUBLIC TicTacToe Board Player)
add_subdirectory(TicTacToe)
add_subdirectory(Board)
add_subdirectory(Player)
