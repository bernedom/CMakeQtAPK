cmake_minimum_required(VERSION 3.21)

project(
  CMakeQtAPKExample
  VERSION 1.0
  DESCRIPTION
    "An example repository to showcase how to build a simple C++ android app with Qt/QML and CMake"
  LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Quick)
set(ANDROID_PACKAGE_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/android"
    CACHE INTERNAL "Android source die for custom AndroidManifest.xml" FORCE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT ANDROID)
  add_executable(QMLDesktopExample)
elseif(ANDROID)
  add_library(QMLDesktopExample SHARED)
  find_package(Qt5 REQUIRED AndroidExtras)
  target_link_libraries(QMLDesktopExample PRIVATE Qt5::AndroidExtras)
  set_target_properties(
    QMLDesktopExample
    PROPERTIES LIBRARY_OUTPUT_NAME CMakeQtAPKExample
               QT_ANDROID_PACKAGE_SOURCE_DIR "${ANDROID_PACKAGE_SOURCE_DIR}")
  add_dependencies(apk QMLDesktopExample)
endif()

target_sources(QMLDesktopExample PRIVATE src/main.cpp src/slideshow.cpp
                                         src/qml/qml.qrc)
target_link_libraries(QMLDesktopExample PRIVATE Qt5::Core Qt5::Quick)
