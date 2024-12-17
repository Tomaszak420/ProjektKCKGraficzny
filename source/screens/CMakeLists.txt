add_library(screens SHARED instructionswindow.cpp leaderboardwindow.cpp gamewindow.cpp mainwindow.cpp leaderboardupdatewindow.cpp)

target_link_libraries(screens PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(screens INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})