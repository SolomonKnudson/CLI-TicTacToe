cmake_minimum_required(VERSION 3.15)

add_library(Player 
	src/player.cpp
)

target_include_directories(Player PUBLIC include)