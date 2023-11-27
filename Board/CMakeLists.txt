cmake_minimum_required(VERSION 3.15)

add_library(Board
	${CMAKE_CURRENT_SOURCE_DIR}/src/board.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/boardDebug.cpp
)

target_include_directories(Board PUBLIC include)