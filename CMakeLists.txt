cmake_minimum_required(VERSION 3.7)
project(apsg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5QuickControls2 REQUIRED)

set(SOURCE_FILES
        main.cc
        apsg.cc)

qt5_add_resources(RCC_SOURCES qml.qrc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RCC_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::QuickControls2)