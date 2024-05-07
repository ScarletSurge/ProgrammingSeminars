cmake_minimum_required(VERSION 3.21)
project(interpreters CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(interpreters main.cpp stack.h stack.c trie.cpp trie.h allocator/allocator.h associative_container/associative_container.h btree/search_tree.h btree/b_tree.h allocator/allocator_guardant.h logger/logger.h logger/logger_guardant.h common/not_implemented.cpp common/not_implemented.h common/operation_not_supported.cpp common/operation_not_supported.h common/typename_holder.h)