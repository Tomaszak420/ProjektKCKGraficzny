cmake_minimum_required(VERSION 3.29)
project(ProjektKCK)

set(CMAKE_CXX_STANDARD 14)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(ProjektKCK
        main.cpp)
target_link_libraries(ProjektKCK ${CURSES_LIBRARIES})
