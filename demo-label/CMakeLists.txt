cmake_minimum_required(VERSION 3.10)
project(MyLabel)
 
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
 
include_directories(${PROJECT_SOURCE_DIR})
 
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
file(GLOB QRCS "*.qrc")
 
add_library(MyLabel SHARED
        ${SRCS}
        ${QRCS})
 
target_link_libraries(MyLabel
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Designer)