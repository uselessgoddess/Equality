cmake_minimum_required(VERSION 3.8)
project(Platform.Equality)

include_directories(../Platform.Equality)

include(FetchContent)

macro(fetch_package package_name)
    FetchContent_MakeAvailable(${package_name})

    FetchContent_GetProperties(${package_name})
    if(NOT ${package_name}_POPULATED)
        FetchContent_Populate(${package_name})
        add_subdirectory(${${package_name}_SOURCE_DIR} ${${package_name}_BINARY_DIR})
        endif()
    endmacro()

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.zip
)

FetchContent_Declare(
        benchmark
        URL https://github.com/google/benchmark/archive/refs/tags/v1.5.3.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

fetch_package(googletest)
fetch_package(benchmark)

add_executable(Platform.Equality.Tests Platform.Equality.Tests.cpp)
set_target_properties(Platform.Equality.Tests PROPERTIES CXX_STANDARD 20)
target_link_libraries(Platform.Equality.Tests PUBLIC gtest gtest_main)

add_executable(Platform.Equality.Benchmark Platform.Equality.Benchmark.cpp)
set_target_properties(Platform.Equality.Benchmark PROPERTIES CXX_STANDARD 20)
target_link_libraries(Platform.Equality.Benchmark PUBLIC benchmark benchmark_main)