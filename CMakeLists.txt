cmake_minimum_required (VERSION 3.7)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#set (CMAKE_VERBOSE_MAKEFILE ON)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

project(sdl_minimal_executable)

find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)

add_subdirectory(src)

set (SOURCES
  main.cpp
  )

add_executable(sdl_minimal_executable
  ${SOURCES}
  )

target_include_directories (sdl_minimal_executable PRIVATE
  )

target_link_libraries(sdl_minimal_executable
  core_utils
  sdl_engine
  sdl_core
  sdl_graphic
  sdl_app_core
  sdl_minimal_dummy
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  )
