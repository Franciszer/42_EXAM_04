cmake_minimum_required(VERSION 3.17)

set(This Tmicroshell)

set(Sources
	Tmicroshell.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
	gtest_main
	microshell)

add_test(
	NAME ${This}
	COMMAND ${This}
)
