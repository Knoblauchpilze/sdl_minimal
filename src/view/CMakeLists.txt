project (sdl_core)

set (CMAKE_CXX_STANDARD 14)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package (SDL REQUIRED)
find_package (SDL_ttf REQUIRED)

set (SOURCES
  Font.cc
  )

add_library (sdl_core SHARED
  ${SOURCES}
  ${SDL_INCLUDE_DIRS}
  ${SDL_TTF_INCLUDE_DIRS}
  )

add_library (SDL IMPORTED SHARED)

set(SDL_CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(sdl_core
  ${SDL_LIBRARY}
  ${SDL_TTF_LIBRARIES}
  )

target_include_directories (sdl_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

