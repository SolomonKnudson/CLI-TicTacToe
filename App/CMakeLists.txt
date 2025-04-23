cmake_minimum_required(VERSION 3.30)

add_executable(CLI-TicTacToe
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(CLI-TicTacToe PRIVATE CLI-TicTacToe::TicTacToe)
