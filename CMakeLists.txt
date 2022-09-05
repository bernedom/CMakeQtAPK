cmake_minimum_required(VERSION 3.21)

project(
  CMakeQtAPKExample
  VERSION 1.0
  DESCRIPTION
    "An example repository to showcase how to build a simple C++ android app with Qt/QML and CMake"
  LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Quick QuickWidgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(SlideShow)
target_sources(SlideShow PRIVATE src/slideshow.cpp)
target_link_libraries(SlideShow PUBLIC Qt5::Core)
target_compile_features(SlideShow PRIVATE cxx_std_17)

add_executable(QMLDesktopExample)
target_sources(QMLDesktopExample PRIVATE src/main.cpp src/qml/qml.qrc)
target_compile_features(QMLDesktopExample PRIVATE cxx_std_17)
target_link_libraries(QMLDesktopExample PRIVATE Qt5::Core Qt5::Quick SlideShow)
