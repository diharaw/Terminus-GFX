
set(GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/gfx_device.h
                ${PROJECT_SOURCE_DIR}/include/gfx/gfx_descs.h
                ${PROJECT_SOURCE_DIR}/include/gfx/gfx_types.h
                ${PROJECT_SOURCE_DIR}/include/gfx/gfx_enums.h)

if (GFX_BACKEND STREQUAL "opengl")
    add_definitions(-DGFX_BACKEND_GL)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/gl/gl_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/gl/gl_types.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/gl/glad.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/gl/khrplatform.h)

    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/gl/gl_device.cpp ${PROJECT_SOURCE_DIR}/src/gl/glad.c)
elseif (GFX_BACKEND STREQUAL "opengles")
    add_definitions(-DGFX_BACKEND_GLES)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/gl/gl_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/gl/gl_types.h)

    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/gl/gl_device.cpp)

    if (NOT EMSCRIPTEN)
        list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/gl/glad.h
                                ${PROJECT_SOURCE_DIR}/include/gfx/gl/khrplatform.h)

        list(APPEND GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/gl/glad.c)
    endif()
elseif (GFX_BACKEND STREQUAL "vulkan")
    add_definitions(-DGFX_BACKEND_VK)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/vk/vk_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/vk/vk_types.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/vk/vk_mem_alloc.h)
    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/vk/vk_device.cpp)
elseif (GFX_BACKEND STREQUAL "direct3d11")
    add_definitions(-DGFX_BACKEND_D3D11)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/d3d11/d3d11_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/d3d11/d3d11_types.h)
    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/d3d11/d3d11_device.cpp)
elseif (GFX_BACKEND STREQUAL "direct3d12")
    add_definitions(-DGFX_BACKEND_D3D12)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/d3d12/d3d12_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/d3d12/d3d12_types.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/d3d12/d3dx12.h)
    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/d3d12/d3d12_device.cpp)
elseif (GFX_BACKEND STREQUAL "metal")
    add_definitions(-DGFX_BACKEND_MTL)

    list(APPEND GFX_HEADERS ${PROJECT_SOURCE_DIR}/include/gfx/mtl/mtl_device.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/mtl/mtl_types.h
                            ${PROJECT_SOURCE_DIR}/include/gfx/mtl/mtl_view.h)
    set(GFX_SOURCE ${PROJECT_SOURCE_DIR}/src/mtl/mtl_device.mm
                   ${PROJECT_SOURCE_DIR}/src/mtl/mtl_view.m)
endif()

if (BUILD_SHARED_LIBRARY)
    add_library(dwGraphics SHARED ${GFX_HEADERS} ${GFX_SOURCE})
else()
    add_library(dwGraphics ${GFX_HEADERS} ${GFX_SOURCE})
endif()

target_link_libraries(dwGraphics ${GFX_LINK_LIBRARIES})