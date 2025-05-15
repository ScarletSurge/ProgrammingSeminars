cmake_minimum_required(VERSION 3.21)
project(course1_cpp_rgu)

set(CMAKE_CXX_STANDARD 20)

add_executable(course1_cpp_rgu main.cpp include/bugint.h src/bugint.cpp include/template_demo.h include/allocator.h include/allocator_with_fit_mode.h include/allocator_guardant.h src/allocator_guardant.cpp include/allocator_sorted_list.h src/allocator_sorted_list.cpp include/not_implemented.h src/not_implemented.cpp include/logger.h src/logger.cpp include/logger_guardant.h src/logger_guardant.cpp include/logger_builder.h src/logger_builder.cpp include/client_logger.h src/client_logger.cpp include/client_logger_builder.h src/client_logger_builder.cpp)
