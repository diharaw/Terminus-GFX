cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project("dwGraphics")

# Set global output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/external")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/external")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Add path for CMake modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Options
set(BUILD_SAMPLES true CACHE BOOL "Build example projects.")
set(BUILD_SHARED_LIBRARY false CACHE BOOL "Build shared library.")

if (NOT EMSCRIPTEN)
	set(GFX_BACKEND "opengl" CACHE STRING "Preferred graphics API to use. Options: opengl, opengles, vulkan, direct3d11, direct3d12, metal")
endif()

# Include directories
set(GFX_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

set(GFX_EXPORT_INCLUDE_DIRS ${GFX_INCLUDE_DIRS} PARENT_SCOPE)

# Graphics API specific settings
if (GFX_BACKEND STREQUAL "opengl")
	message(STATUS "Building with OpenGL backend")

	# Find packages
	find_package(OpenGL REQUIRED)

	# Libraries
	set(GFX_LINK_LIBRARIES ${OPENGL_LIBRARIES})
elseif(GFX_BACKEND STREQUAL "opengles")
	message(STATUS "Building with OpenGL ES backend")

	# Find packages
	find_package(OpenGLES2 REQUIRED)
	find_package(OpenGLES3 REQUIRED)
	find_package(EGL REQUIRED)

	# Libraries
	set(GFX_LINK_LIBRARIES ${EGL_INCLUDE_DIR} 
						   ${OPENGLES2_INCLUDE_DIR} 
						   ${OPENGLES3_INCLUDE_DIR})

	# Append includes
	list(APPEND GFX_INCLUDE_DIRS "${OPENGLES2_INCLUDE_DIR}" 
								 "${OPENGLES3_INCLUDE_DIR}" 
								 "${EGL_INCLUDE_DIR}")
elseif(GFX_BACKEND STREQUAL "vulkan")
	message(STATUS "Building with Vulkan backend")

	# Find packages
	find_package(Vulkan REQUIRED)

	# Libraries
	set(GFX_LINK_LIBRARIES ${VULKAN_LIBRARY})

	# Append includes
	list(APPEND GFX_INCLUDE_DIRS ${VULKAN_INCLUDE_DIR})
elseif(GFX_BACKEND STREQUAL "direct3d11")
	message(STATUS "Building with Direct3D 11 backend")

	# Libraries
	set(GFX_LINK_LIBRARIES "d3d11.lib" 
						   "dxgi.lib" 
						   "d3dcompiler.lib")
elseif(GFX_BACKEND STREQUAL "direct3d12")
	message(STATUS "Building with Direct3D 12 backend")

	# Libraries
	set(GFX_LINK_LIBRARIES "d3d12.lib" 
						   "dxgi.lib" 
						   "d3dcompiler.lib")
elseif(GFX_BACKEND STREQUAL "metal")
	message(STATUS "Building with Metal backend")
else()
	message(FATAL_ERROR "Unknown backend specified! Please use one of these backend names: opengl, opengles, vulkan, direct3d11, direct3d12, metal")
endif()

include_directories(${GFX_INCLUDE_DIRS})

add_subdirectory("src")

if (BUILD_SAMPLES)
	add_subdirectory("example")
endif()