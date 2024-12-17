cmake_minimum_required(VERSION 3.16)

project(ProjektKCKGraficzny2 VERSION 0.5.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/source/main.cpp
        ${PROJECT_SOURCE_DIR}/source/screens/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/source/screens/mainwindow.h

        ${PROJECT_SOURCE_DIR}/source/screens/mainwindow.ui
        ${PROJECT_SOURCE_DIR}/source/screens/instructionswindow.ui
        ${PROJECT_SOURCE_DIR}/source/screens/instructionswindow.cpp
        ${PROJECT_SOURCE_DIR}/source/screens/leaderboardwindow.ui
        ${PROJECT_SOURCE_DIR}/source/screens/leaderboardwindow.cpp
        ${PROJECT_SOURCE_DIR}/source/screens/leaderboardupdatewindow.ui
        ${PROJECT_SOURCE_DIR}/source/screens/leaderboardupdatewindow.cpp
        ${PROJECT_SOURCE_DIR}/source/screens/gamewindow.ui
        ${PROJECT_SOURCE_DIR}/source/screens/gamewindow.cpp

        ${PROJECT_SOURCE_DIR}/source/dictionary/Dictionary.cpp
        ${PROJECT_SOURCE_DIR}/source/dictionary/dictionary.txt
        ${PROJECT_SOURCE_DIR}/source/board/BoardAnalyzer.cpp 
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ProjektKCKGraficzny2
        MANUAL_FINALIZATION

        ${PROJECT_SOURCES}
        
        #Dictionary.h GameFunctions.h GameState.h InstructionsFunctions.h Leaderboard.h 
        #BoardAnalyzer.h MenuFunctions.h ScreenChoice.h
        #instructionswindow.h instructionswindow.cpp instructionswindow.ui

        #Leaderboard.cpp
        #LeaderboardItem.h
        #leaderboardwindow.h leaderboardwindow.cpp leaderboardwindow.ui
        #leaderboardupdatewindow.h leaderboardupdatewindow.cpp leaderboardupdatewindow.ui
        #gamewindow.h gamewindow.cpp gamewindow.ui
        #BoardAnalyzer.cpp GameState.cpp
        #Dictionary.cpp
        #dictionary.txt
        
    )

else()
    if(ANDROID)
        add_library(ProjektKCKGraficzny2 SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(ProjektKCKGraficzny2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_subdirectory(source)
target_link_libraries(ProjektKCKGraficzny2 PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets PUBLIC board dictionary leaderboard screens game)

target_include_directories(ProjektKCKGraficzny2 PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/source/board"
                            "${PROJECT_SOURCE_DIR}/source/leaderboard"
                            "${PROJECT_SOURCE_DIR}/source/screens"
                            "${PROJECT_SOURCE_DIR}/source/game"
                            "${PROJECT_SOURCE_DIR}/source/coordinates"
                            "${PROJECT_SOURCE_DIR}/source/dictionary"
                            )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/source/dictionary/dictionary.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#target_link_libraries(ProjektKCKGraficzny2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ProjektKCKGraficzny2)
endif()
set_target_properties(ProjektKCKGraficzny2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ProjektKCKGraficzny2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ProjektKCKGraficzny2)
endif()
