cmake_minimum_required(VERSION 3.16)
project(Platform.Equality)

add_library(Platform.Equality.Lib INTERFACE)
target_include_directories(Platform.Equality.Lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})