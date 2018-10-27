project (ogamelike_lib_app)

set (CMAKE_CXX_STANDARD 14)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

set (SOURCES
  ArgumentsException.cpp
  ArgumentsParser.cpp
  )

add_library (ogamelike_lib_app SHARED
  ${SOURCES}
  )

set(APP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_include_directories (ogamelike_lib_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

