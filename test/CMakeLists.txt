cmake_minimum_required(VERSION 3.16)

project("acmlib-test")

add_executable(
    ${PROJECT_NAME}
    Main.cpp
    GeometryTest.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "..")
