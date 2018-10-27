cmake_minimum_required (VERSION 3.1)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set (CMAKE_VERBOSE_MAKEFILE ON)

project(sdlminimal)

add_subdirectory(src)

set (SOURCES
  main.cpp
  )

add_executable(sdlminimal
  ${SOURCES}
  )

target_include_directories (sdlminimal PRIVATE
  )

target_link_libraries(sdlminimal
  sdl_core
  )
