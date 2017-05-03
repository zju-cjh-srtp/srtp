cmake_minimum_required(VERSION 3.4)
project(srtp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c generate.h generate.c firstFit.h firstFit.c greedy.h greedy.c state.c state.h)
add_executable(srtp ${SOURCE_FILES})