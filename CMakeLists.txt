cmake_minimum_required(VERSION 3.21)
project(interpreters CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(interpreters main.cpp stack.h stack.c trie.cpp trie.h)