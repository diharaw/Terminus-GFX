#pragma once

#if defined(__APPLE__)

#include <objc/objc-runtime.h>
#include <stdint.h>

namespace MTL
{
    class IndexBuffer;
    class RenderPass;
    class Framebuffer;
    
    class CommandBuffer
    {
    public:
        CommandBuffer(id queue);
        ~CommandBuffer();
        void Begin();
        void End();
        void BeginRenderPass(RenderPass* renderPass, Framebuffer* frameBuffer, float* clearColor);
        void EndRenderPass();
        
    private:
        id                          m_MTLCommandBuffer;
        id                          m_MTLEncoder;
        id                          m_MTLQueue;
        uint32_t                    m_Primitive;
        IndexBuffer*                m_LastIBO;
        RenderPass*                 m_CurrentRenderPass;
    };
}

#endif
