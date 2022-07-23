cmake_minimum_required(VERSION 3.16)

project("acmlib-benchmark")
find_package(benchmark REQUIRED)
set(CMAKE_CXX_STANDARD 17 REQURIED)
add_executable(
    ${PROJECT_NAME}
    GeometryBM.cpp
)
target_compile_options(${PROJECT_NAME} PRIVATE -O2)
target_include_directories(${PROJECT_NAME} PRIVATE "..")
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark_main)
