cmake_minimum_required(VERSION 3.21)
project(puksrenjk)

set(CMAKE_CXX_STANDARD 14)

add_executable(puksrenjk main.cpp include/int_wrapper.h src/int_wrapper.cpp include/priority_queue.h include/binomial_priority_queue.h src/binomial_priority_queue.cpp)
