cmake_minimum_required(VERSION 3.15)

add_library(Board
	${CMAKE_CURRENT_SOURCE_DIR}/src/boardTableLogic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/boardUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/isWinConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/debug/setWinConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/debug/clearWinConFig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/debug/isValidWinCase.cpp
)

target_include_directories(Board PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

