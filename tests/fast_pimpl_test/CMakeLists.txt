project(test_fast_pimpl)

add_executable(${PROJECT_NAME}
  book.cpp
  book.h
  example.cpp
  example.h
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  LINK_PRIVATE
    GTest::GTest
    GTest::Main

    tiny_utils
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION tests COMPONENT tests)
