cmake_minimum_required(VERSION 3.21)
project(course1_cpp_rgu)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(course1_cpp_rgu main.cpp include/bugint.h src/bugint.cpp include/template_demo.h include/allocator.h include/allocator_with_fit_mode.h include/allocator_guardant.h src/allocator_guardant.cpp include/allocator_sorted_list.h src/allocator_sorted_list.cpp include/not_implemented.h src/not_implemented.cpp include/logger.h src/logger.cpp include/logger_guardant.h src/logger_guardant.cpp include/logger_builder.h src/logger_builder.cpp include/client_logger.h src/client_logger.cpp include/client_logger_builder.h src/client_logger_builder.cpp include/binary_search_tree.h include/search_tree.h include/associative_container.h)
target_link_libraries(
        course1_cpp_rgu
        PUBLIC
        nlohmann_json::nlohmann_json)
add_custom_command(
        TARGET course1_cpp_rgu
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:course1_cpp_rgu>)