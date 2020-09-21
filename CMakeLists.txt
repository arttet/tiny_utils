cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(TinyUtils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_HEADERS_IN_COMPILE_COMMANDS ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(GNUInstallDirs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(WITH_DOC OFF CACHE BOOL "Build documentations")
set(WITH_TESTS OFF CACHE BOOL "Build test suite")

if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
  add_compile_options(
    "-Wextra"
    "-Wall"
    "-Werror"
  )

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
      "-Wno-c++98-compat"
      "-Wno-c++98-compat-pedantic"
      "-Wno-global-constructors"
      "-Wno-language-extension-token"
      "-Wno-undef"
      "-Wno-shift-sign-overflow"
    )
  endif()
endif()

if (MSVC)
  add_compile_options("/WX" "/W4" "/EHsc")

  add_compile_definitions(_SCL_SECURE_NO_WARNINGS)
  add_compile_definitions(_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
  add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
endif ()

if (CMAKE_CXX_CLANG_TIDY)
  list(APPEND CMAKE_CXX_CLANG_TIDY
    "-format-style='file'"
  )
endif()

if (CMAKE_CXX_CPPCHECK)
  list(APPEND CMAKE_CXX_CPPCHECK
    "--std=c++11"
    "--enable=warning,performance,portability,information,missingInclude"
    "--inconclusive"
    "--force"
    "--inline-suppr"
    "--quiet"
    "--suppressions-list=${CMAKE_SOURCE_DIR}/.CppCheckSuppressions"
  )
endif()

if (CMAKE_CXX_INCLUDE_WHAT_YOU_USE)
  list(APPEND CMAKE_CXX_INCLUDE_WHAT_YOU_USE
    "-Xiwyu"
  )
endif()

add_subdirectory(include)

if (WITH_DOC)
  find_package(Doxygen REQUIRED dot)

  set(DOXYGEN_DOCDIR ${CMAKE_BINARY_DIR}/doc)
  set(DOXYGEN_IN "${CMAKE_SOURCE_DIR}/.github/Doxyfile.in")
  set(DOXYGEN_OUT Doxyfile)
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  add_custom_target(build_doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )

  install(
    DIRECTORY ${DOXYGEN_DOCDIR}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
  )
endif()

if (WITH_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

install(FILES LICENSE README.md DESTINATION .)

if (BUILD_SHARED_LIBS)
  foreach(RUNTIME_DESTINATION IN ITEMS tests)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${RUNTIME_DESTINATION})
    include(InstallRequiredSystemLibraries)
  endforeach()
endif ()

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
include (CPack)
