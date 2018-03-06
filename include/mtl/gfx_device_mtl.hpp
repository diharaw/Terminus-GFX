#include "mtl_macros.h"
#include <stdio.h>
#include <stdint.h>
#include <objc/objc-runtime.h>
#include <dispatch/dispatch.h>

#include "Remotery.h"

#define METAL_SHADER_ENTRY_POINT "shaderEntry"

namespace gfx
{
#define MAX_RENDER_TARGETS 8
#define MAX_FRAMEBUFFERS 8
    
    namespace ShaderType
    {
        enum
        {
            VERTEX = 0,
            GEOMETRY,
            TESS_CONTROL,
            TESS_EVAL,
            PIXEL,
            COMPUTE
        };
    };
    
    namespace DataType
    {
        enum
        {
            BYTE   = 0,
            UBYTE  = 1,
            INT16  = 2,
            INT32  = 3,
            UINT16 = 4,
            UINT32 = 5,
            FLOAT  = 6
        };
    };
    
    namespace PrimitiveType
    {
        enum
        {
            POINT           = 0,
            LINE            = 1,
            LINE_STRIP      = 2,
            TRIANGLE        = 3,
            TRIANGLE_STRIP  = 4
        };
    };
    
    struct DeviceCreateDesc
    {
        void* window;
    };

    struct CommandPool
    {
        void* encoder;
    };
    
    struct Fence
    {
#if defined(TE_PLATFORM_IPHONE)
        id         mtl_fence;
#else
        bool                 initial;
        dispatch_semaphore_t sema;
#endif
    };
 
    struct RenderPass
    {
        id renderPassDescMTL;
        uint32_t numRenderTargets;
        uint32_t renderTargetFormats[MAX_RENDER_TARGETS];
        uint32_t depthTargetFormat;
    };
    
    struct VertexBuffer
    {
        id MTLBuffer;
    };
    
    struct IndexBuffer
    {
        id MTLBuffer;
        uint32_t type;
    };

    struct ConstantBuffer
    {
        id MTLBuffer;
    };
    
    struct InputLayout
    {
        id MTLVertexDesc;
    };
    
    struct VertexArray
    {
        VertexBuffer* vbuf;
        IndexBuffer*  ibuf;
    };
    
    struct PipelineState
    {
        id MTLPipelineState;
        id MTLDepthStencilState;
    };
    
    struct Shader
    {
        uint32_t type;
        id    MTLLibrary;
        id    MTLFunction;
    };
    
    struct InputElementDesc
    {
        uint32_t	num_sub_elements;
        uint32_t    type;
        bool		normalized;
        uint32_t	offset;
        const char* semantic_name;
    };
    
    struct InputLayoutDesc
    {
        InputElementDesc* elements;
        uint32_t         vertex_size;
        uint32_t         num_elements;
    };
    
    struct PipelineStateCreateDesc
    {
        Shader*        vert;
        Shader*        geo;
        Shader*        tess_control;
        Shader*        tess_eval;
        Shader*        pixel;
        Shader*        compute;
        RenderPass*    render_pass;
        InputLayout*   layout;
    };
    
    struct ShaderCreateDesc
    {
        const char* source;
        void*       binary;
        size_t      size;
        uint32_t    type;
    };
    
    struct ConstantBufferCreateDesc
    {
        uint32_t size;
        void*  data;
    };
    
    struct VertexBufferCreateDesc
    {
        uint32_t size;
        void*  data;
    };
    
    struct IndexBufferCreateDesc
    {
        uint32_t size;
        void*  data;
        uint32_t type;
    };
    
    struct Texture
    {
        id MTLTexture;
    };
    
    struct Texture2D : public Texture
    {
        
    };
 
    struct Framebuffer
    {
        uint32_t numRenderTargets;
        Texture* renderTargets[MAX_RENDER_TARGETS];
        Texture* depthTarget;
    };
    
    struct DescriptorSet
    {
        
    };
    
    struct DescriptorHeap
    {
        
    };
    
    struct Texture2DCreateDesc
    {
        
    };
    
    struct RenderPassCreateDesc
    {
        uint32_t numRenderTargets;
        uint32_t renderTargetFormats[MAX_RENDER_TARGETS];
    };

    struct FramebufferCreateDesc
    {
        uint32_t  numRenderTargets;
        Texture** renderTargets;
        Texture*  depthTarget;
    };
    
    struct VertexArrayCreateDesc
    {
        VertexBuffer* vbuf;
        IndexBuffer*  ibuf;
        InputLayout*  layout;
    };
    
    class CommandBuffer
    {
    public:
        friend class Device;
        
        CommandBuffer();
        ~CommandBuffer();
        void Begin();
        void BeginRenderPass(RenderPass* renderPass, Framebuffer* frameBuffer, float* clearColor);
        void End();
        void EndRenderPass();
        
        Texture* DefaultFramebuffer();
        void SetPrimitiveType(uint32_t type);
        void BindVertexArray(VertexArray* vao);
        void BindPipelineState(PipelineState* pso);
        void bind_constant_buffer(ConstantBuffer* cb, uint32_t slot, uint32_t offset, uint32_t shader_type);
        void Draw(uint32_t first_index, uint32_t count);
        void DrawIndexed(uint32_t index_count);
        void DrawIndexedBaseVertex(uint32_t index_count, uint32_t base_index, uint32_t base_vertex);
        
    private:
        id                          m_cmd_buf;
        id                          m_encoder;
        id                          m_queue;
        uint32_t                    m_primitive;
        IndexBuffer*                m_last_ibo;
        RenderPass*                 current_rp;
    };

    class Device
    {
    public:
        Device();
        ~Device();
        bool            Init(DeviceCreateDesc desc);
        void            Shutdown();
        void            Submit(uint32_t count, CommandBuffer** buffers, Fence* fence = nullptr);
        void            Present();
        void            WaitForFence(Fence* fence);
        Framebuffer*    DefaultFramebuffer();
        
        CommandPool*    CreateCommandPool();
        CommandBuffer*  CreateCommandBuffer(CommandPool* pool);
        Fence*          CreateFence();
        Framebuffer*    CreateFramebuffer(const FramebufferCreateDesc& desc);
        RenderPass*     CreateRenderPass(const RenderPassCreateDesc& desc);
        Texture2D*      CreateTexture2D(const Texture2DCreateDesc& desc);
        VertexBuffer*   CreateVertexBuffer(const VertexBufferCreateDesc& desc);
        VertexArray*    CreateVertexArray(const VertexArrayCreateDesc& desc);
        IndexBuffer*    CreateIndexBuffer(const IndexBufferCreateDesc& desc);
        ConstantBuffer* CreateConstantBuffer(const ConstantBufferCreateDesc& desc);
        PipelineState*  CreatePipelineState(const PipelineStateCreateDesc& desc);
        Shader*         CreateShader(const ShaderCreateDesc desc);
        InputLayout*    CreateInputLayout(const InputLayoutDesc& desc);
        
    private:
        void AquireNextFramebuffer();
        
    private:
        struct MetalContext;
    
        id                   m_MTLDevice;
        id                   m_MTLQueue;
        id                   m_MTLDefaultCommandBuffer;
        MetalContext*        m_MTLContext;
        uint32_t             m_FramebufferIndex = 0;
        Texture*             m_DepthTexture;
        Texture*             m_ColorTextures[MAX_FRAMEBUFFERS];
        Framebuffer*         m_DefaultFramebuffers[MAX_FRAMEBUFFERS];
        Framebuffer*         m_CurrentFramebuffer;
    };
}
