cmake_minimum_required(VERSION 3.21)

project(
  CMakeQtAPKExample
  VERSION 1.0
  DESCRIPTION
    "An example repository to showcase how to build a simple C++ android app with Qt/QML and CMake"
  LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Quick QuickWidgets Gui)
set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT ANDROID)
  add_executable(QMLDesktopExample)
elseif(ANDROID)
  add_library(QMLDesktopExample SHARED)
  find_package(Qt5 REQUIRED AndroidExtras)
  target_link_libraries(QMLDesktopExample PRIVATE Qt5::AndroidExtras)
  set_target_properties(QMLDesktopExample PROPERTIES LIBRARY_OUTPUT_NAME CMakeQtAPKExample)
  add_dependencies(apk QMLDesktopExample)
endif()

target_sources(QMLDesktopExample PRIVATE src/main.cpp src/slideshow.cpp src/qml/qml.qrc)
target_link_libraries(QMLDesktopExample PRIVATE Qt5::Core Qt5::Quick)
