cmake_minimum_required(VERSION 3.10)

set(This micro_lib)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 99)
set(POSITION_INDEPENDENT_CODE ON)

project(${This} CXX C)
include (CTest)

add_subdirectory(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/srcs/)

set(Headers
	${CMAKE_CURRENT_SOURCE_DIR}/srcs/microshell.h
)

set(Sources
	${CMAKE_CURRENT_SOURCE_DIR}/srcs/microshell.c
)

add_library(${This} STATIC ${Sources} ${Headers})

target_include_directories(${This} PUBLIC Headers Sources)
target_compile_options(${This} PUBLIC -Wall -Wextra -Werror)

add_subdirectory(test)

set(MICROSHELL microshell)

add_executable(${MICROSHELL} srcs/main.c)

target_include_directories(${MICROSHELL} PUBLIC Headers Sources)
target_compile_options(${MICROSHELL} PUBLIC -Wall -Wextra -Werror)
target_link_libraries(${MICROSHELL} PUBLIC
	micro_lib
)


