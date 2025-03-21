
add_executable(CLI-TicTacToe
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(CLI-TicTacToe PRIVATE TicTacToe)
target_compile_features(CLI-TicTacToe PRIVATE cxx_std_17)
