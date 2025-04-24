cmake_minimum_required(VERSION 3.21)
project(course1_cpp_rgu)

set(CMAKE_CXX_STANDARD 20)

add_executable(course1_cpp_rgu main.cpp include/bugint.h src/bugint.cpp include/template_demo.h include/allocator.h include/allocator_with_fit_mode.h include/allocator_guardant.h src/allocator_guardant.cpp include/allocator_sorted_list.h src/allocator_sorted_list.cpp include/not_implemented.h src/not_implemented.cpp)
