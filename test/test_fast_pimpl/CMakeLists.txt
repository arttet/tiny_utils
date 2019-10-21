cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(TARGET_NAME "test_fast_pimpl")
project(${TARGET_NAME})

add_executable(${TARGET_NAME}
  example.cpp
  example.h
  main.cpp
)

target_link_libraries(${TARGET_NAME}
  LINK_PRIVATE
    GTest::GTest
    GTest::Main

    util
)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME}
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

install(TARGETS ${TARGET_NAME} DESTINATION test COMPONENT test)
