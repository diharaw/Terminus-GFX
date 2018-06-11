#pragma once

#include <gfx/gfx_enums.h>
#include <gfx/gfx_descs.h>

#if defined(GFX_BACKEND_GL) || defined(GFX_BACKEND_GLES)
#include <gfx/gl/gl_types.h>
#elif defined(GFX_BACKEND_VK)
#include <gfx/vk/vk_types.h>
#elif defined(GFX_BACKEND_D3D11)
#include <gfx/d3d11/d3d11_types.h>
#elif defined(GFX_BACKEND_D3D11)
#include <gfx/d3d12/d3d12_types.h>
#elif defined(GFX_BACKEND_MTL)
#include <gfx/mtl/mtl_types.h>
#endif