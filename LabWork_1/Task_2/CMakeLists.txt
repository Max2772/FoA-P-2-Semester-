cmake_minimum_required(VERSION 3.16)

project(Task_2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Task_2
  main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
  romb.cpp figure.cpp paintscene.cpp triangle.cpp
  rectangle.cpp ellipse.cpp star.cpp polygon.cpp
  parallelogram.cpp paint.cpp
  triangle.h triangle.cpp star.h star.cpp romb.h romb.cpp
  rectangle.h rectangle.cpp polygon.h polygon.cpp parallelogram.h
  parallelogram.cpp paintscene.h paintscene.cpp paint.h paint.cpp
  mainwindow.ui mainwindow.h mainwindow.cpp main.cpp figure.h
  figure.cpp ellipse.h ellipse.cpp CMakeLists.txt.user CMakeLists.txt
)

target_link_libraries(Task_2 PRIVATE Qt6::Widgets)

set_target_properties(Task_2 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
