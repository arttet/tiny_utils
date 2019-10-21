cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(util LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE headers "util/*.h")

add_custom_target(util_interface SOURCES ${headers})

add_library(util INTERFACE)

target_include_directories(util
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

option(WITH_TEST "Build tests" OFF)
if (WITH_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
