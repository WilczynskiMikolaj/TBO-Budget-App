cmake_minimum_required(VERSION 3.16)
project(TBO-Budget-App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(TBO-Budget-App
    src/main.cpp
)

target_link_libraries(TBO-Budget-App PRIVATE Qt6::Widgets)