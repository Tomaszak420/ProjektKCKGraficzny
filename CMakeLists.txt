cmake_minimum_required(VERSION 3.29)
project(ProjektKCK)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES Leaderboard.cpp
                LeaderboardFunctions.cpp
                LeaderboardUpdateFunctions.cpp
                GameFunctions.cpp 
                GameState.cpp 
                InstructionsFunctions.cpp
                LeaderboardItem.h 
                MenuFunctions.cpp
                BoardAnalyzer.cpp
                Dictionary.cpp
                dictionary.txt)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(ProjektKCK main.cpp ${SOURCES})
add_subdirectory(testygoogle)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(ProjektKCK ${CURSES_LIBRARIES})
