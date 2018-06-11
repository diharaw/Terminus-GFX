#pragma once

#if defined(GFX_BACKEND_GL) || defined(GFX_BACKEND_GLES)
#include <gfx/gl/gl_device.h>
#elif defined(GFX_BACKEND_VK)
#include <gfx/vk/vk_device.h>
#elif defined(GFX_BACKEND_D3D11)
#include <gfx/d3d11/d3d11_device.h>
#elif defined(GFX_BACKEND_D3D11)
#include <gfx/d3d12/d3d12_device.h>
#elif defined(GFX_BACKEND_MTL)
#include <gfx/mtl/mtl_device.h>
#endif
