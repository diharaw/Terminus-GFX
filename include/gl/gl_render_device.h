#pragma once

#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <gfx_types.h>

class RenderDevice
{
public:
    RenderDevice();
    ~RenderDevice();
	bool init();
	Shader* create_shader(const char* source, uint32_t type);
	ShaderProgram* create_shader_program(Shader** shaders, uint32_t count);
	Framebuffer*	 create_framebuffer(const FramebufferCreateDesc& desc);
	void attach_render_target(Framebuffer* framebuffer, const RenderTargetDesc& desc);
	void attach_depth_stencil_target(Framebuffer* framebuffer, const DepthStencilTargetDesc& desc);
    InputLayout* create_input_layout(const InputLayoutCreateDesc& desc);
	VertexBuffer* create_vertex_buffer(const BufferCreateDesc& desc);
	IndexBuffer* create_index_buffer(const BufferCreateDesc& desc);
	VertexArray* create_vertex_array(const VertexArrayCreateDesc& desc);
	Texture2D* create_texture_2d(const Texture2DCreateDesc& desc);
	TextureCube* create_texture_cube(const TextureCubeCreateDesc& desc);
	void generate_mipmaps(Texture* texture);
	void wait_for_idle();
	UniformBuffer* create_uniform_buffer(const BufferCreateDesc& desc);
	PipelineStateObject* create_pipeline_state_object(const PipelineStateObjectCreateDesc& desc);
	RasterizerState* create_rasterizer_state(const RasterizerStateCreateDesc& desc);
	SamplerState* create_sampler_state(const SamplerStateCreateDesc& desc);
	DepthStencilState* create_depth_stencil_state(const DepthStencilStateCreateDesc& desc);
	int uniform_buffer_alignment();

	void destroy(Shader* shader);
	void destroy(ShaderProgram* program);
	void destroy(VertexBuffer* vertex_buffer);
	void destroy(IndexBuffer* index_buffer);
	void destroy(VertexArray* vertex_array);
	void destroy(UniformBuffer* buffer);
	void destroy(Texture* texture);
	void destroy(Framebuffer* framebuffer);
	void destroy(RasterizerState* state);
	void destroy(SamplerState* state);
	void destroy(DepthStencilState* state);
    void destroy(PipelineStateObject* pso);

	void  texture_extents(Texture* texture, const int& mipSlice, int& width, int& height);
	void  texture_data(Texture* texture, const int& mipSlice, const int& arraySlice, void* data);
	void  bind_pipeline_state_object(PipelineStateObject* pso);
	void  bind_texture(Texture* texture, uint32_t shader_stage, uint32_t slot);
	void  bind_rasterizer_state(RasterizerState* state);
	void  bind_sampler_state(SamplerState* state, uint32_t shader_stage, uint32_t slot);
	void  bind_vertex_array(VertexArray* vertex_array);
	void  bind_uniform_buffer(UniformBuffer* uniform_buffer, uint32_t shader_stage, uint32_t buffer_slot);
    void  bind_uniform_buffer_range(UniformBuffer* uniform_buffer, uint32_t shader_stage, uint32_t buffer_slot, size_t offset, size_t size);
	void  bind_framebuffer(Framebuffer* framebuffer);
	void  bind_depth_stencil_state(DepthStencilState* state);
	void  bind_shader_program(ShaderProgram* program);
	void* map_buffer(Buffer* buffer, uint32_t type);
	void  unmap_buffer(Buffer* buffer);

	void  set_primitive_type(uint32_t primitive);
	void  clear_framebuffer(uint32_t clear_target, float* clear_color);
	void  set_viewport(uint32_t width, uint32_t height, uint32_t top_left_x, uint32_t top_left_y);

	void draw(uint32_t first_index, uint32_t count);
	void draw_indexed(uint32_t index_count);
	void draw_indexed_base_vertex(uint32_t index_count, uint32_t base_index, uint32_t base_vertex);
    
private:
    DeviceData m_device_data;
};
