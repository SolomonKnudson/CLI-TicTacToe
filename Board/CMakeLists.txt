cmake_minimum_required(VERSION 3.15)

add_library(Board
	src/board.cpp
	src/boardDebug.cpp
)

target_include_directories(Board PUBLIC include)