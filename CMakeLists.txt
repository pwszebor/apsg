cmake_minimum_required(VERSION 3.7)
project(apsg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -larmadillo")

find_package(Qt5QuickControls2 REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(SOURCE_FILES
        main.cc
        apsg.cc
        lms.cc
        plot.cc
        QCustomPlot-source/qcustomplot-source/qcustomplot.cpp)

include_directories(QCustomPlot-source/qcustomplot-source)

qt5_add_resources(RCC_SOURCES qml.qrc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RCC_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::PrintSupport Qt5::QuickControls2 armadillo pthread)