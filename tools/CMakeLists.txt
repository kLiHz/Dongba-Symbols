cmake_minimum_required(VERSION 3.23)
project(tools)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(grid "grid.cpp")
target_link_libraries(grid ${OpenCV_LIBS})
