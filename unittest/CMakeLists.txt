cmake_minimum_required(VERSION 3.16)

project("acmlib-test")
set(CMAKE_CXX_STANDARD 17 REQURIED)
add_executable(
    ${PROJECT_NAME}
    Main.cpp
    GeometryTest.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "..")
