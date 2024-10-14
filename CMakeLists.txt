cmake_minimum_required(VERSION 3.21)
project(ProgrammingSeminars C)

set(CMAKE_C_STANDARD 99)

add_executable(ProgrammingSeminars main.c include/dump.h src/dump.c include/unidirectional_list.h src/unidirectional_list.c)
