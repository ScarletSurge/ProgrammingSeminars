cmake_minimum_required(VERSION 3.21)
project(interpreters C)

set(CMAKE_C_STANDARD 99)

add_executable(interpreters main.c stack.h stack.c)