#include <d3d11/d3d11_render_device.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "utility.h"
#include "logger.h"

RenderDevice::RenderDevice()
{
    
}

RenderDevice::~RenderDevice()
{
    
}

bool RenderDevice::init()
{

}

Shader* RenderDevice::create_shader(const char* source, uint32_t type)
{

}

ShaderProgram* RenderDevice::create_shader_program(Shader** shaders, uint32_t count)
{

}

void RenderDevice::attach_render_target(Framebuffer* framebuffer, const RenderTargetDesc& desc)
{

}

void RenderDevice::attach_depth_stencil_target(Framebuffer* framebuffer, const DepthStencilTargetDesc& desc)
{

}

Framebuffer* RenderDevice::create_framebuffer(const FramebufferCreateDesc& desc)
{

}

VertexBuffer* RenderDevice::create_vertex_buffer(const BufferCreateDesc& desc)
{

}

UniformBuffer* RenderDevice::create_uniform_buffer(const BufferCreateDesc& desc)
{

}

IndexBuffer* RenderDevice::create_index_buffer(const BufferCreateDesc& desc)
{

}

InputLayout* RenderDevice::create_input_layout(const InputLayoutCreateDesc& desc)
{

}

VertexArray* RenderDevice::create_vertex_array(const VertexArrayCreateDesc& desc)
{

}

Texture2D* RenderDevice::create_texture_2d(const Texture2DCreateDesc& desc)
{

}

Texture2D* RenderDevice::create_texture_2d_array(const Texture2DArrayCreateDesc& desc)
{

}

TextureCube* RenderDevice::create_texture_cube(const TextureCubeCreateDesc& desc)
{

}

void RenderDevice::set_texture_data(Texture* texture, const int& mipSlice, const int& arraySlice, uint16_t& width, uint16_t& height, void* data)
{

}

void RenderDevice::generate_mipmaps(Texture* texture)
{

}

void RenderDevice::wait_for_idle()
{
	
}

RasterizerState* RenderDevice::create_rasterizer_state(const RasterizerStateCreateDesc& desc)
{

}

DepthStencilState* RenderDevice::create_depth_stencil_state(const DepthStencilStateCreateDesc& desc)
{

}

BlendState* RenderDevice::create_blend_state(const BlendStateCreateDesc& desc)
{

}

SamplerState* RenderDevice::create_sampler_state(const SamplerStateCreateDesc& desc)
{

}

void RenderDevice::destroy(Shader* shader)
{

}

void RenderDevice::destroy(ShaderProgram* program)
{

}

void RenderDevice::destroy(VertexBuffer* vertex_buffer)
{

}

void RenderDevice::destroy(IndexBuffer* index_buffer)
{

}

void RenderDevice::destroy(UniformBuffer* buffer)
{

}

void RenderDevice::destroy(VertexArray* vertex_array)
{

}

void RenderDevice::destroy(Texture* texture)
{

}

void RenderDevice::destroy(RasterizerState* state)
{
	
}

void RenderDevice::destroy(BlendState* state)
{
	
}

void RenderDevice::destroy(SamplerState* state)
{
	
}

void RenderDevice::destroy(DepthStencilState* state)
{

}

void RenderDevice::destroy(PipelineStateObject* pso)
{
	
}

void RenderDevice::destroy(Framebuffer* framebuffer)
{

}

void RenderDevice::texture_extents(Texture* texture, const int& mipSlice, int& width, int& height)
{

}

void RenderDevice::texture_data(Texture* texture, const int& mipSlice, const int& arraySlice, void* data)
{

}

void RenderDevice::bind_pipeline_state_object(PipelineStateObject* pso)
{

}

int RenderDevice::uniform_buffer_alignment()
{

}

void RenderDevice::bind_texture(Texture* texture, uint32_t shader_stage, uint32_t buffer_slot)
{

}

void RenderDevice::bind_uniform_buffer(UniformBuffer* uniform_buffer, uint32_t shader_stage, uint32_t buffer_slot)
{

}

void RenderDevice::bind_uniform_buffer_range(UniformBuffer* uniform_buffer, uint32_t shader_stage, uint32_t buffer_slot, size_t offset, size_t size)
{
	
}

void RenderDevice::bind_vertex_array(VertexArray* vertex_array)
{

}

void RenderDevice::bind_rasterizer_state(RasterizerState* state)
{

}

void RenderDevice::bind_sampler_state(SamplerState* state, uint32_t shader_stage, uint32_t slot)
{

}

void RenderDevice::bind_blend_state(BlendState* state)
{

}

void RenderDevice::bind_framebuffer(Framebuffer* framebuffer)
{

}

void RenderDevice::bind_depth_stencil_state(DepthStencilState* state)
{

}

void RenderDevice::bind_shader_program(ShaderProgram* program)
{

}

void* RenderDevice::map_buffer(Buffer* buffer, uint32_t type)
{

}

void RenderDevice::unmap_buffer(Buffer* buffer)
{

}

void RenderDevice::set_primitive_type(uint32_t primitive)
{
	
}

void RenderDevice::clear_framebuffer(uint32_t clear_target, float* clear_color)
{

}

void RenderDevice::set_viewport(uint32_t width, uint32_t height, uint32_t top_left_x, uint32_t top_left_y)
{
	
}

void RenderDevice::dispatch_compute(uint32_t x, uint32_t y, uint32_t z)
{

}

void RenderDevice::draw(uint32_t first_index, uint32_t count)
{
	
}

void RenderDevice::draw_indexed(uint32_t index_count)
{

}

void RenderDevice::draw_indexed_base_vertex(uint32_t index_count, uint32_t base_index, uint32_t base_vertex)
{

}
