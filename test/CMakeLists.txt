cmake_minimum_required(VERSION 3.16)

project("acmlib-test")

file(GLOB_RECURSE "TEST_SOURCES" "./*.cpp")
add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "..")
