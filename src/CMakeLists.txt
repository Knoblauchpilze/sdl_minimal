project (sdl_minimal_dummy)

set (CMAKE_CXX_STANDARD 14)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)

set (SOURCES
  GenericWidget.cc
  )

add_library (sdl_minimal_dummy SHARED
  ${SOURCES}
  )

set(SDL_MINIMAL_DUMMY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(sdl_minimal_dummy
  ${SDL2_LIBRARY}
  ${SDL2_TTF_LIBRARIES}
  sdl_core
  sdl_graphic
  )

target_include_directories (sdl_minimal_dummy PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
