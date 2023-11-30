cmake_minimum_required(VERSION 3.15)

add_library(Player 
	${CMAKE_CURRENT_SOURCE_DIR}/src/player.cpp
)

target_include_directories(Player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/player.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
	install(TARGETS Player DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()