#cmake ver req
cmake_minimum_required(VERSION 2.8)

set(project_name sfml_directx)

#project name
project(${project_name})

set(CMAKE_BUILD_TYPE DebugBuild)

#so that it talks to us
set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions("-DMYMATH_USE_SSE2")
add_definitions("-DMYMATH_USE_FMA")
add_definitions("-DMYMATH_FORCE_INLINE")

if(${CMAKE_BUILD_TYPE} STREQUAL DebugBuild)
  add_definitions("-DDebugBuild")
  message("Debug mode")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL ReleaseBuild)
  add_definitions("-DReleaseBuild")
  message("Release mode")
endif()

#header files source
include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/external/include/)
link_directories(${CMAKE_SOURCE_DIR}/external/lib/)

include_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.10240.0\\um")
include_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.10240.0\\shared")
link_directories("C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.10240.0\\um\\x86")

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
endif()

if(WIN32)
	set(${project_name}_external_libs
		optimized sfml-audio debug sfml-audio-d
		optimized sfml-graphics debug sfml-graphics-d
		optimized sfml-main debug sfml-main-d
		optimized sfml-network debug sfml-network-d
		optimized sfml-system debug sfml-system-d
		optimized sfml-window debug sfml-window-d
		debug override_new-d
		optimized override_new
		d3d12 dxgi
	)
endif()

#adding the project's exe
add_executable(${project_name} main)

#set_target_properties(${project_name} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")

target_link_libraries(${project_name} ${${project_name}_external_libs})
