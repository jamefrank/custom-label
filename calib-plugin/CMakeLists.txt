cmake_minimum_required(VERSION 3.10)
project(MyLabel1)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
 
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Designer
        REQUIRED)
 
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/*.h)
file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
file(GLOB_RECURSE Q_PLUGIN RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS plugin/*.*)
 
 
add_library(${LIBRARY_NAME} SHARED 
        ${QT_SOURCES} 
        ${QT_MOC}
        ${Q_PLUGIN}
        ${QT_FORMS}
        ${QT_RESOURCES}
        )
 
target_link_libraries(${LIBRARY_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Designer)