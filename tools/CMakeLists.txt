cmake_minimum_required(VERSION 3.23)
project(tools)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(rename "rename.cpp")

add_executable(grid "grid.cpp")
target_link_libraries(grid ${OpenCV_LIBS} Boost::program_options)

add_executable(cut "cut.cpp")
target_link_libraries(cut ${OpenCV_LIBS} Boost::program_options)
