cmake_minimum_required(VERSION 3.10)

set(This gtest_microshell)

set(Sources
	${CMAKE_CURRENT_SOURCE_DIR}/srcs/Tmicroshell.cpp
)

add_executable(${This} ${Sources})
target_include_directories(${This} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/srcs/)
target_link_libraries(${This} PUBLIC
	gtest_main
	micro_lib
)

add_test(
	NAME ${This}
	COMMAND ${This}
)
