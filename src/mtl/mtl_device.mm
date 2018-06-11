#include <gfx/mtl/mtl_device.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <stdio.h>
#include <assert.h>

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>
#import <Metal/Metal.h>
#import <gfx/mtl/mtl_view.h>

#define MTL_OBJECT(type, variable) variable
#define MTL_DEVICE(variable) MTL_OBJECT(MTLDevice, variable)
#define MTL_CMD_QUEUE(variable) MTL_OBJECT(MTLCommandQueue, variable)
#define MTL_BUFFER(variable) MTL_OBJECT(MTLBuffer, variable)
#define MTL_TEXTURE(variable) MTL_OBJECT(MTLTexture, variable)
#define MTL_LIBRARY(variable) MTL_OBJECT(MTLLibrary, variable)
#define MTL_DRAWABLE(variable) MTL_OBJECT(MTLDrawable, variable)
#define MTL_FUNCTION(variable) MTL_OBJECT(MTLFunction, variable)
#define MTL_CMD_BUFFER(variable) MTL_OBJECT(MTLCommandBuffer, variable)
#define MTL_DEPTH_STENCIL_STATE(variable) MTL_OBJECT(MTLDepthStencilState, variable)
#define MTL_RENDER_PIPELINE_STATE(variable) MTL_OBJECT(MTLRenderPipelineState, variable)
#define MTL_RENDER_CMD_ENCODER(variable) MTL_OBJECT(MTLRenderCommandEncoder, variable)
#define MTL_VOID_PTR(variable) (__bridge void*)variable

namespace gfx
{
    const MTLVertexFormat g_vertex_format_tbl[][4] =
    {
        { MTLVertexFormatChar2, MTLVertexFormatChar2, MTLVertexFormatChar3, MTLVertexFormatChar4 }, // BYTE
        { MTLVertexFormatUChar2, MTLVertexFormatUChar2, MTLVertexFormatUChar3, MTLVertexFormatUChar4 }, // UBYTE
        { MTLVertexFormatShort2, MTLVertexFormatShort2, MTLVertexFormatShort3, MTLVertexFormatShort4 }, // INT16
        { MTLVertexFormatInt, MTLVertexFormatInt2, MTLVertexFormatInt3, MTLVertexFormatInt4 }, // INT32
        { MTLVertexFormatUShort2, MTLVertexFormatUShort2, MTLVertexFormatUShort3, MTLVertexFormatUShort4 }, // UINT16
        { MTLVertexFormatUInt, MTLVertexFormatUInt2, MTLVertexFormatUInt3, MTLVertexFormatUInt4 }, // UINT32
        { MTLVertexFormatFloat, MTLVertexFormatFloat2, MTLVertexFormatFloat3, MTLVertexFormatFloat4 } //  FLOAT
    };
    
    const MTLIndexType g_index_type_tbl[] =
    {
        MTLIndexTypeUInt16,
        MTLIndexTypeUInt16,
        MTLIndexTypeUInt16,
        MTLIndexTypeUInt32,
        MTLIndexTypeUInt32,
        MTLIndexTypeUInt32,
        MTLIndexTypeUInt32
    };
    
    const MTLPrimitiveType g_primitive_type_tbl[] =
    {
        MTLPrimitiveTypePoint,
        MTLPrimitiveTypeLine,
        MTLPrimitiveTypeLineStrip,
        MTLPrimitiveTypeTriangle,
        MTLPrimitiveTypeTriangleStrip
    };

    struct Device::MetalContext
    {
        NSWindow*  m_nswindow;
        MetalView* m_view;
    };
    
    CommandBuffer::CommandBuffer()
    {
        
    }
    
    CommandBuffer::~CommandBuffer()
    {
        
    }
    
    void CommandBuffer::Begin()
    {
        [m_cmd_buf release];
        m_cmd_buf = nil;
        m_cmd_buf = [MTL_CMD_QUEUE(m_queue) commandBuffer];
        
//        rmt_BindMetal(m_cmd_buf);
    }
    
    void CommandBuffer::End()
    {
        
    }
    
    void CommandBuffer::BeginRenderPass(RenderPass* renderPass, Framebuffer* frameBuffer, float* clearColor)
    {
        assert(current_rp == nullptr);
        current_rp = renderPass;
        
        MTLRenderPassDescriptor* rpDesc = renderPass->renderPassDescMTL;
        
        for (uint32_t i = 0; i < frameBuffer->numRenderTargets; i++)
        {
            rpDesc.colorAttachments[i].texture = frameBuffer->renderTargets[i]->MTLTexture;
            rpDesc.colorAttachments[i].clearColor = MTLClearColorMake(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
            rpDesc.colorAttachments[i].loadAction = MTLLoadActionClear;
            rpDesc.colorAttachments[i].storeAction = MTLStoreActionStore;
        }
        
        if(frameBuffer->depthTarget)
        {
            rpDesc.depthAttachment.texture = frameBuffer->depthTarget->MTLTexture;
            rpDesc.depthAttachment.clearDepth = 1.0;
            rpDesc.depthAttachment.loadAction = MTLLoadActionClear;
            rpDesc.depthAttachment.storeAction = MTLStoreActionDontCare;
        }
        
        if(renderPass->renderPassDescMTL)
        {
            TE_RELEASE(m_encoder);
            m_encoder = [m_cmd_buf renderCommandEncoderWithDescriptor:rpDesc];
        }
    }

    
    void CommandBuffer::EndRenderPass()
    {
        [m_encoder endEncoding];
        assert(current_rp != nullptr);
        current_rp = nullptr;
    }
    
    void CommandBuffer::BindVertexArray(VertexArray* vao)
    {
        assert(vao);
        assert(vao->vbuf);
        
        [m_encoder setVertexBuffer:vao->vbuf->MTLBuffer offset:0 atIndex:0];
        m_last_ibo = vao->ibuf;
    }
    
    void CommandBuffer::BindPipelineState(PipelineState* pso)
    {
        assert(pso);
        assert(pso->MTLDepthStencilState);
        [m_encoder setRenderPipelineState:pso->MTLPipelineState];
        [m_encoder setDepthStencilState:pso->MTLDepthStencilState];
    }
    
    void CommandBuffer::bind_constant_buffer(ConstantBuffer* cb, uint32_t slot, uint32_t offset, uint32_t shader_type)
    {
//        switch (shader_type)
//        {
//            case ShaderType::VERTEX:
//            {
//                m_encoder.SetVertexBuffer(cb->mtl_buffer, offset, slot);
//                break;
//            }
//            case ShaderType::GEOMETRY:
//            {
//                m_encoder.SetFragmentBuffer(cb->mtl_buffer, offset, slot);
//                break;
//            }
//
//            default:
//                break;
//        }
    }
    
    void CommandBuffer::SetPrimitiveType(uint32_t type)
    {
        m_primitive = g_primitive_type_tbl[type];
    }
    
    void CommandBuffer::Draw(uint32_t first_index, uint32_t count)
    {
        [m_encoder drawPrimitives:(MTLPrimitiveType)m_primitive vertexStart:first_index vertexCount:count];
    }
    
    void CommandBuffer::DrawIndexed(uint32_t index_count)
    {
        assert(m_last_ibo);
        [m_encoder drawIndexedPrimitives:(MTLPrimitiveType)m_primitive
                                                      indexCount:index_count
                                                       indexType:(MTLIndexType)m_last_ibo->type
                                                     indexBuffer:MTL_BUFFER(m_last_ibo->MTLBuffer)
                                               indexBufferOffset:index_count];
    }
    
    void CommandBuffer::DrawIndexedBaseVertex(uint32_t index_count, uint32_t base_index, uint32_t base_vertex)
    {
        assert(m_last_ibo);
        [m_encoder drawIndexedPrimitives:(MTLPrimitiveType)m_primitive
                                                      indexCount:index_count
                                                       indexType:(MTLIndexType)m_last_ibo->type
                                                     indexBuffer:MTL_BUFFER(m_last_ibo->MTLBuffer)
                                               indexBufferOffset:base_index
                                                   instanceCount:1
                                                      baseVertex:base_vertex
                                                    baseInstance:0];
    }
    
    Device::Device() : m_MTLContext(new MetalContext())
    {
        
    }
    
    Device::~Device()
    {

    }
    
    bool Device::Init(DeviceCreateDesc desc)
    {
        m_MTLDevice = MTLCreateSystemDefaultDevice();
        
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);
        SDL_GetWindowWMInfo((SDL_Window*)desc.window, &info);
        
        m_MTLContext->m_nswindow = info.info.cocoa.window;
        
        m_MTLContext->m_view = [[MetalView alloc] initWithDevice:m_MTLDevice
                                                 withFrame:m_MTLContext->m_nswindow.contentView.frame
                                                 withWindow:m_MTLContext->m_nswindow];
        
        [[m_MTLContext->m_nswindow contentView] addSubview:m_MTLContext->m_view];
        
        [m_MTLContext->m_nswindow center];
        [m_MTLContext->m_nswindow orderFrontRegardless];
        
        [[m_MTLContext->m_nswindow contentView] setWantsLayer:YES];
        [[m_MTLContext->m_nswindow contentView] setLayer:[m_MTLContext->m_view metalLayer]];
        
        m_MTLQueue = [m_MTLDevice newCommandQueue];
        
        for(uint32_t i = 0; i < MAX_FRAMEBUFFERS; i++)
        {
            m_ColorTextures[i] = new Texture2D();
            m_DefaultFramebuffers[i] = new Framebuffer();
        }
        
        m_DepthTexture = new Texture2D();
        m_DepthTexture->MTLTexture = [m_MTLContext->m_view depthTexture];
        
        AquireNextFramebuffer();
        
        return true;
    }
    
    void Device::Shutdown()
    {
        TE_RELEASE(m_MTLDefaultCommandBuffer);
        TE_RELEASE(m_MTLQueue);
        TE_RELEASE(m_MTLDevice);
        
        delete m_DepthTexture;
        
        for(uint32_t i = 0; i < MAX_FRAMEBUFFERS; i++)
        {
            delete m_ColorTextures[i];
            delete m_DefaultFramebuffers[i];
        }
        
        [[m_MTLContext->m_nswindow contentView] setWantsLayer:NO];
        [[m_MTLContext->m_nswindow contentView] setLayer:nil];
        
        [m_MTLContext->m_view removeFromSuperview];
        [m_MTLContext->m_view dealloc];
        
        if(m_MTLContext)
            delete m_MTLContext;
    }

    void Device::Submit(uint32_t count, CommandBuffer** buffers, Fence* fence)
    {
        if(buffers)
        {
            for(uint32_t i = 0; i < count; i++)
            {
                if(fence && i == (count - 1))
                {
                    fence->initial = false;
                    [buffers[i]->m_cmd_buf addCompletedHandler:^(id<MTLCommandBuffer> commandBuffer) {
                        dispatch_semaphore_signal(fence->sema);
                    }];
                }
   
                [buffers[i]->m_cmd_buf commit];
            }
        }
    }
    
    void Device::AquireNextFramebuffer()
    {
        [m_MTLContext->m_view nextDrawable];
        ++m_FramebufferIndex;
        
        uint32_t index = (m_FramebufferIndex - 1) % MAX_FRAMEBUFFERS;
        m_CurrentFramebuffer = m_DefaultFramebuffers[index];
        
        m_CurrentFramebuffer->numRenderTargets = 1;
        
        Texture* texture = m_ColorTextures[index];
        texture->MTLTexture = [m_MTLContext->m_view colorTexture];
        m_CurrentFramebuffer->renderTargets[0] = texture;
        m_CurrentFramebuffer->depthTarget = m_DepthTexture;
    }
    
    void Device::Present()
    {
        m_MTLDefaultCommandBuffer = [MTL_CMD_QUEUE(m_MTLQueue) commandBuffer];
        [MTL_CMD_BUFFER(m_MTLDefaultCommandBuffer) presentDrawable:[m_MTLContext->m_view currentDrawable]];
        [MTL_CMD_BUFFER(m_MTLDefaultCommandBuffer) commit];

        TE_RELEASE(m_MTLDefaultCommandBuffer);

        AquireNextFramebuffer();
    }
    
    void Device::WaitForFence(Fence* fence)
    {
        if(fence->initial)
            return;
            
        dispatch_semaphore_wait(fence->sema, DISPATCH_TIME_FOREVER);
    }

    CommandPool* Device::CreateCommandPool()
    {
        CommandPool* pool = new CommandPool();
        return pool;
    }
    
    CommandBuffer* Device::CreateCommandBuffer(CommandPool* pool)
    {
        CommandBuffer* buffer = new CommandBuffer();
        
        buffer->m_queue = m_MTLQueue;
        buffer->current_rp = nullptr;
        
        return buffer;
    }
    
    Fence* Device::CreateFence()
    {
        Fence* fence = new Fence();
        
#if defined(TE_PLATFORM_IPHONE)
        fence->mtl_fence = m_device.NewFence();
#else
        fence->initial = true;
        fence->sema = dispatch_semaphore_create(0);
#endif
        return fence;
    }
    
    RenderPass* Device::CreateRenderPass(const RenderPassCreateDesc& desc)
    {
        RenderPass* render_pass = new RenderPass();
        
        render_pass->numRenderTargets = desc.numRenderTargets;
        render_pass->renderPassDescMTL = [[MTLRenderPassDescriptor alloc] init];
        MTLRenderPassDescriptor* rpDesc = render_pass->renderPassDescMTL;
        
        for (uint32_t i = 0; i < desc.numRenderTargets; i++)
        {
            MTLRenderPassColorAttachmentDescriptor* desc = [[MTLRenderPassColorAttachmentDescriptor alloc] init];
            [rpDesc.colorAttachments setObject:desc atIndexedSubscript:i];
            TE_RELEASE(desc);
        }

        return render_pass;
    }
    
    Framebuffer* Device::CreateFramebuffer(const FramebufferCreateDesc& desc)
    {
        Framebuffer* fb = new Framebuffer();
        
        memcpy(&fb->renderTargets[0], desc.renderTargets, sizeof(Texture*) * desc.numRenderTargets);
        fb->depthTarget = desc.depthTarget;
        
        return fb;
    }
    
    VertexBuffer* Device::CreateVertexBuffer(const VertexBufferCreateDesc& desc)
    {
        VertexBuffer* buf = new VertexBuffer();
        buf->MTLBuffer = [m_MTLDevice newBufferWithBytes:desc.data length:desc.size options:MTLResourceOptionCPUCacheModeDefault];

        if(buf->MTLBuffer)
            return buf;
        else
        {
            delete buf;
            return nullptr;
        }
    }
    
    IndexBuffer* Device::CreateIndexBuffer(const IndexBufferCreateDesc& desc)
    {
        IndexBuffer* buf = new IndexBuffer();
        
        buf->MTLBuffer = [m_MTLDevice newBufferWithBytes:desc.data length:desc.size options:MTLResourceOptionCPUCacheModeDefault];
        buf->type = g_index_type_tbl[desc.type];
        
        if(buf->MTLBuffer)
            return buf;
        else
        {
            delete buf;
            return nullptr;
        }
    }
    
    ConstantBuffer* Device::CreateConstantBuffer(const ConstantBufferCreateDesc& desc)
    {
        ConstantBuffer* buf = new ConstantBuffer();
        
        if(desc.data)
            buf->MTLBuffer = [m_MTLDevice newBufferWithBytes:desc.data length:desc.size options:MTLResourceOptionCPUCacheModeDefault];
        else
            buf->MTLBuffer = [MTL_DEVICE(m_MTLDevice) newBufferWithLength:desc.size options:MTLResourceOptionCPUCacheModeDefault];
        
        if(buf->MTLBuffer)
            return buf;
        else
        {
            delete buf;
            return nullptr;
        }
    }
    
    VertexArray* Device::CreateVertexArray(const VertexArrayCreateDesc& desc)
    {
        if(!desc.vbuf)
            return nullptr;
        
        VertexArray* vao = new VertexArray();
        
        vao->vbuf = desc.vbuf;
        vao->ibuf = desc.ibuf;
        
        return vao;
    }

    Shader* Device::CreateShader(const ShaderCreateDesc desc)
    {
        Shader* shader = new Shader();
        
        shader->type = desc.type;
        
        if(desc.binary)
        {
            dispatch_data_t data = dispatch_data_create(desc.binary,
                                                        desc.size,
                                                        NULL,
                                                        DISPATCH_DATA_DESTRUCTOR_DEFAULT);
            
            NSError *error = nil;
            shader->MTLLibrary = [MTL_DEVICE(m_MTLDevice) newLibraryWithData:data error:&error];
        }
        else if (desc.source)
        {
            NSError *error = nil;
            MTLCompileOptions* options = [MTLCompileOptions new];
            shader->MTLLibrary = [MTL_DEVICE(m_MTLDevice) newLibraryWithSource:[NSString stringWithUTF8String:desc.source] options:options error:&error];
            
            TE_RELEASE(options);
        }
        else
        {
            delete shader;
            return nullptr;
        }

        if(shader->MTLLibrary)
        {
            shader->MTLFunction = [shader->MTLLibrary newFunctionWithName:@METAL_SHADER_ENTRY_POINT];
   
            if(shader->MTLFunction)
                return shader;
        }
        
        delete shader;
        return nullptr;
    }

    InputLayout* Device::CreateInputLayout(const InputLayoutDesc& desc)
    {
        InputLayout* ia = new InputLayout();
        
        ia->MTLVertexDesc = [MTLVertexDescriptor new];
        MTLVertexDescriptor* vertDesc = ia->MTLVertexDesc;
        
        for(uint32_t i = 0; i < desc.num_elements; i++)
        {
            vertDesc.attributes[i].bufferIndex = 0;
            vertDesc.attributes[i].format = g_vertex_format_tbl[desc.elements[i].type][desc.elements[i].num_sub_elements - 1];
            vertDesc.attributes[i].offset = desc.elements[i].offset;
        }
        
        vertDesc.layouts[0].stride = desc.vertex_size;
        vertDesc.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
        
        return ia;
    }
    
    Framebuffer* Device::DefaultFramebuffer()
    {
        return m_CurrentFramebuffer;
    }
    
    PipelineState* Device::CreatePipelineState(const PipelineStateCreateDesc& desc)
    {
        PipelineState* pso = new PipelineState();
        MTLRenderPipelineDescriptor* pipelineDesc = [MTLRenderPipelineDescriptor new];
        
        MTLDepthStencilDescriptor *depthStencilDescriptor = [MTLDepthStencilDescriptor new];
        depthStencilDescriptor.depthCompareFunction = MTLCompareFunctionLess;
        depthStencilDescriptor.depthWriteEnabled = YES;
        pso->MTLDepthStencilState = [MTL_DEVICE(m_MTLDevice) newDepthStencilStateWithDescriptor:depthStencilDescriptor];
        
        if(desc.vert && desc.pixel)
        {
            [pipelineDesc setVertexFunction:desc.vert->MTLFunction];
            [pipelineDesc setFragmentFunction:desc.pixel->MTLFunction];
        }
        else
        {
            delete pso;
            return nullptr;
        }

        for(uint32_t i = 0; i < desc.render_pass->numRenderTargets; i++)
            pipelineDesc.colorAttachments[i].pixelFormat = MTLPixelFormatBGRA8Unorm; //(MTLPixelFormat)desc.render_pass->renderTargetFormats[i];
            
        pipelineDesc.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float; // (MTLPixelFormat)desc.render_pass->depthTargetFormat;
        pipelineDesc.vertexDescriptor = desc.layout->MTLVertexDesc;
        
        NSError *error = nil;
        pso->MTLPipelineState = [MTL_DEVICE(m_MTLDevice) newRenderPipelineStateWithDescriptor:pipelineDesc error:&error];
        
        TE_RELEASE(pipelineDesc);
        TE_RELEASE(depthStencilDescriptor);
        
        return pso;
    }
}
