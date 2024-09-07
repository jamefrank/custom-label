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
 
# include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})
 
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
file(GLOB QRCS "*.qrc")
 
add_library(${LIBRARY_NAME} SHARED
        ${SRCS}
        ${QRCS})
 
target_link_libraries(${LIBRARY_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Designer)