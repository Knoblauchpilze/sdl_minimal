
add_library (sdl_minimal_lib SHARED)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories (sdl_minimal_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (sdl_minimal_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Content.cc
	)

target_link_libraries(sdl_minimal_lib
	sdl_core
	)
