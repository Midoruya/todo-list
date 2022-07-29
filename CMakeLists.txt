cmake_minimum_required(VERSION 3.0.0)
project(todo_list VERSION 0.1.0 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(todo_list src/main.cpp)
add_library(command_handler src/command_handler/command_handler.cpp)
add_library(console_table src/console_table/console_table.cpp)

target_link_libraries(todo_list command_handler console_table)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
