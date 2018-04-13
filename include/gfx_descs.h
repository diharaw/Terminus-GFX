#pragma once

#include <stdint.h>

#define MAX_RENDER_TARGETS 16

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
    void*    data;
    uint32_t format;
    uint16_t mipmap_levels;
};

struct Texture2DCreateDesc
{
    uint16_t width;
    uint16_t height;
    void*    data;
    uint32_t format;
    uint16_t mipmap_levels;
};

struct Texture2DArrayCreateDesc
{
	uint16_t width;
	uint16_t height;
	uint32_t format;
	uint16_t mipmap_levels;
	uint16_t array_slices;
};

struct Texture3DCreateDesc
{
    uint16_t width;
    uint16_t height;
    uint16_t depth;
    void*    data;
    uint32_t format;
    uint16_t mipmap_levels;
};

struct TextureCubeCreateDesc
{
    uint16_t width;
    uint16_t height;
    void*    initialData[6];
    uint32_t format;
    uint16_t mipmapLevels;
};

struct BufferCreateDesc
{
    void*	 data;
    uint32_t size;
    uint32_t usage_type;
    uint32_t data_type;
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
	uint32_t arraySlice;
	uint32_t mipSlice;
};

struct DepthStencilTargetDesc
{
	Texture* texture;
	uint32_t arraySlice;
	uint32_t mipSlice;
};

struct FramebufferCreateDesc
{
	uint32_t			   renderTargetCount;
	RenderTargetDesc       renderTargets[MAX_RENDER_TARGETS];
	DepthStencilTargetDesc depthStencilTarget;
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

struct SamplerStateCreateDesc
{
    uint32_t min_filter;
    uint32_t mag_filter;
    uint32_t wrap_mode_u;
    uint32_t wrap_mode_v;
    uint32_t wrap_mode_w;
    float    max_anisotropy;
    float    border_color[4];
};

struct ShaderCreateDesc
{
    uint32_t    type;
    const char* shader_source;
};

struct ShaderProgramCreateDesc
{
    Shader* vertex;
    Shader* pixel;
    Shader* geometry;
    Shader* tessellation_control;
    Shader* tessellation_evaluation;
};

struct BlendStateCreateDesc
{
    
};

struct PipelineStateObjectCreateDesc
{
    DepthStencilStateCreateDesc depth_stencil_state;
    RasterizerStateCreateDesc   rasterizer_state;
    BlendStateCreateDesc        blend_state;
    uint32_t                    primitive;
};
