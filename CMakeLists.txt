cmake_minimum_required(VERSION 3.17)

set(This microshell)
set(CMAKE_CXX_STANDARD 98)
set(POSITION_INDEPENDENT_CODE ON)

project(${This} CXX)
enable_testing()

add_subdirectory(googletest)

include_directories(.
					srcs/)

set(Headers
	srcs/microshell.h
)

set(Sources
	srcs/microshell.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

target_compile_options(${This} PRIVATE -c -Wall -Wextra -Werror -fsanitize=address)

add_subdirectory(test)