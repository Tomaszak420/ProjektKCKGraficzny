# 'Google_test' is the subproject name
project(Google_tests)

include_directories(${CURSES_INCLUDE_DIR})
# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-1.15.2/googletest-1.15.2)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Curses REQUIRED)
# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(Google_Tests_run
        menuTest.cpp
        GameStateTest.cpp
        BoardAnalyzer.cpp
        Dictionary.cpp


)
target_link_libraries(Google_Tests_run gtest gtest_main ${CURSES_LIBRARIES} pthread ncurses)
# LeaderboardTest.cpp DZIAŁA usunąc reszte trzeba
#LeaderboardFunctionsTest.cpp
#GameFunctionTest.cpp