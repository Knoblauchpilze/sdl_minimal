project (sdl_minimal_dummy)

set (CMAKE_CXX_STANDARD 14)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

set (SOURCES
  Content.cc
  )

add_library (sdl_minimal_dummy SHARED
  ${SOURCES}
  )

set (SDL_MINIMAL_DUMMY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(sdl_minimal_dummy
  sdl_core
  )

target_include_directories (sdl_minimal_dummy PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
