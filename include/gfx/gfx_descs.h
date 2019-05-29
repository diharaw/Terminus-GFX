#pragma once

#include <stdint.h>
#include <gfx/gfx_enums.h>

struct Shader;
struct InputElement;
struct InputLayout;
struct VertexBuffer;
struct IndexBuffer;
struct Texture;

struct RenderDeviceInitData
{
    void*  memory;
    size_t size;
};

struct Texture1DCreateDesc
{
    uint16_t width;
	TextureFormat format;
    uint16_t array_slices;
    uint16_t mipmap_levels;
    uint32_t flags;
};

struct Texture2DCreateDesc
{
    uint16_t width;
    uint16_t height;
	TextureFormat format;
    uint16_t array_slices;
    uint16_t mipmap_levels;
    uint32_t flags;
};

struct Texture3DCreateDesc
{
    uint16_t width;
    uint16_t height;
    uint16_t depth;
	TextureFormat format;
    uint16_t mipmap_levels;
    uint32_t flags;
};

struct TextureCubeCreateDesc
{
    uint16_t width;
    uint16_t height;
	TextureFormat format;
    uint16_t array_slices;
    uint16_t mipmapLevels;
    uint32_t flags;
};

struct BufferCreateDesc
{
    uint32_t size;
	BufferUsage usage_type;
	DataType data_type;
};

struct InputLayoutCreateDesc
{
    InputElement* elements;
    uint32_t	  vertex_size;
    uint32_t	  num_elements;
};

struct VertexArrayCreateDesc
{
    VertexBuffer* vertex_buffer;
    IndexBuffer*  index_buffer;
    InputLayout*  layout;
};

struct RenderTargetDesc
{
	Texture* texture;
	uint32_t array_slice;
	uint32_t mip_slice;
};

struct DepthStencilTargetDesc
{
	Texture* texture;
	uint32_t array_slice;
	uint32_t mip_slice;
};

struct DepthStencilStateCreateDesc
{
    bool     enable_depth_test;
    bool     enable_stencil_test;
    bool     depth_mask;
    uint32_t depth_cmp_func;
    uint32_t front_stencil_fail;
    uint32_t front_stencil_pass_depth_fail;
    uint32_t front_stencil_pass_depth_pass;
    uint32_t front_stencil_cmp_func;
    uint32_t back_stencil_fail;
    uint32_t back_stencil_pass_depth_fail;
    uint32_t back_stencil_pass_depth_pass;
    uint32_t back_stencil_cmp_func;
    uint32_t stencil_mask;
};

struct RasterizerStateCreateDesc
{
    uint32_t cull_mode;
    uint32_t fill_mode;
    bool     front_winding_ccw;
    bool     multisample;
    bool     scissor;
};

struct SamplerCreateDesc
{
    uint32_t min_filter;
    uint32_t mag_filter;
    uint32_t wrap_mode_u;
    uint32_t wrap_mode_v;
    uint32_t wrap_mode_w;
    uint32_t comparison_mode;
    uint32_t comparison_func;
    float    max_anisotropy;
    float    border_color[4];
};

struct ShaderCreateDesc
{
    uint32_t type;
    char* shader_source;
};

struct ShaderProgramCreateDesc
{
	uint32_t num_shaders;
    Shader** shaders;
};

struct BlendStateCreateDesc
{
	bool enable;
	uint32_t src_func;
	uint32_t dst_func;
	uint32_t blend_op;
	uint32_t src_func_alpha;
	uint32_t dst_func_alpha;
	uint32_t blend_op_alpha;
};