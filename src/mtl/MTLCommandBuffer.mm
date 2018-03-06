#include "MTLCommandBuffer.h"
#include "../../mtl_macros.h"

#import <Metal/Metal.h>

namespace MTL
{
    CommandBuffer::CommandBuffer(id queue)
    {
        m_MTLQueue = queue;
        m_MTLCommandBuffer = nil;
        m_CurrentRenderPass = nullptr;
    }
    
    CommandBuffer::~CommandBuffer()
    {
        TE_RELEASE(m_MTLCommandBuffer);
    }
    
    void CommandBuffer::Begin()
    {
        TE_RELEASE(m_MTLCommandBuffer);
        m_MTLCommandBuffer = [m_MTLQueue commandBuffer];
    }
    
    void CommandBuffer::End()
    {
        
    }
    
    void CommandBuffer::BeginRenderPass(RenderPass* renderPass, Framebuffer* frameBuffer, float* clearColor)
    {
        TE_RELEASE(m_MTLEncoder);
        
    }
    
    void CommandBuffer::EndRenderPass()
    {
        
    }
}
