add_custom_target(tiny_utils_interface
  SOURCES
    tiny_utils/fast_pimpl.h
    tiny_utils/numeric_traits.h
)

add_library(tiny_utils INTERFACE)

target_include_directories(tiny_utils
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tiny_utils
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
)
