cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(OpenGL REQUIRED)

set (CMAKE_CXX_STANDARD 11)

set(GFX_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories("${PROJECT_SOURCE_DIR}/include")

set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/gl/gl_render_device.cpp
			   ${PROJECT_SOURCE_DIR}/src/gl/utility.cpp
			   ${PROJECT_SOURCE_DIR}/src/gl/logger.cpp)

set(GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gl/gl_render_device.h
				${PROJECT_SOURCE_DIR}/include/gl/gl_types.h
				${PROJECT_SOURCE_DIR}/include/gfx_descs.h
				${PROJECT_SOURCE_DIR}/include/render_device.h			
				${PROJECT_SOURCE_DIR}/include/gfx_enums.h
				${PROJECT_SOURCE_DIR}/include/gfx_types.h
				${PROJECT_SOURCE_DIR}/src/gl/utility.h
				${PROJECT_SOURCE_DIR}/src/gl/logger.h)

if (NOT EMSCRIPTEN)
	list(APPEND GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/gl/gl_core_4_5.c)
	list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/src/gl/gl_core_4_5.h)
endif()

add_library(Terminus-GFX ${GFX_HEADERS} ${GFX_SOURCE})				
					   
target_link_libraries(Terminus-GFX ${OPENGL_LIBRARIES})

if(EMSCRIPTEN)
    set_target_properties(Terminus-GFX PROPERTIES CMAKE_CXX_FLAGS "-s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 --std=c++11")
endif()