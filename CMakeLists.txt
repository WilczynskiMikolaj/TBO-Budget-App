cmake_minimum_required(VERSION 3.16)
project(TBO-Budget-App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(TBO-Budget-App
    src/main.cpp
    src/Calculator.cpp
    src/Calculator.h
    src/CSVStorage.cpp
    src/CSVStorage.h
    src/Entry.h
    src/MainWindow.cpp
    src/MainWindow.h
    src/mainwindow.ui
    src/Statistics.cpp
    src/Statistics.h
    src/mainwindow.ui
    src/Recents.h 
    src/Recents.cpp
    src/entrytablemodel.h 
    src/entrytablemodel.cpp

)

target_link_libraries(TBO-Budget-App PRIVATE Qt6::Widgets)