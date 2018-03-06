//
//  mtl_context.m
//  Test
//
//  Created by Dihara Wijetunga on 6/26/17.
//
//

#include "mtl_macros.h"

#import "metal_view.h"
#import <Foundation/Foundation.h>

@implementation MetalView
{
    CAMetalLayer*            _metalLayer;
    NSWindow*                _nswindow;
    id <CAMetalDrawable>     _drawable;
    MTLRenderPassDescriptor* _renderPass;
    id<MTLTexture>           _depthTexture;
}

- (id) initWithDevice:(id <MTLDevice>) device withFrame:(CGRect)frame withWindow:(NSWindow*)window
{
    if ((self = [super initWithFrame:frame]))
    {
        _metalLayer = [[CAMetalLayer layer] retain];
        _metalLayer.opaque = YES;
        _metalLayer.device = device;
        _metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        _nswindow = window;
        self.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
        
        _renderPass = [MTLRenderPassDescriptor renderPassDescriptor];
        
        [self updateDrawableSize];
    }
    
    return self;
}

- (void)dealloc
{
    [_metalLayer release];
    [super dealloc];
}

+ (Class)layerClass
{
    return [CAMetalLayer class];
}

- (CAMetalLayer*) metalLayer
{
    return _metalLayer;
}

- (void)updateDrawableSize
{
    CGFloat scale = [NSScreen mainScreen].backingScaleFactor;
    CGSize drawableSize = [_nswindow contentView].bounds.size;
    
    drawableSize.width *= scale;
    drawableSize.height *= scale;
    
    _metalLayer.drawableSize = drawableSize;
    [self makeDepthTexture];
}

- (void)makeDepthTexture
{
    CGSize drawableSize = self.metalLayer.drawableSize;
    
    if ([_depthTexture width] != drawableSize.width ||
        [_depthTexture height] != drawableSize.height)
    {
        TE_RELEASE(_depthTexture);
        
        MTLTextureDescriptor *desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatDepth32Float
                                                                                        width:drawableSize.width
                                                                                       height:drawableSize.height
                                                                                    mipmapped:NO];
        desc.usage = MTLTextureUsageRenderTarget;
        desc.resourceOptions = MTLResourceStorageModePrivate;
        
        _depthTexture = [self.metalLayer.device newTextureWithDescriptor:desc];
//        TE_RELEASE(desc); // Causes crash upto resize event
    }
}

- (void) setFrame:(NSRect)frame
{
    [super setFrame:frame];
    [self updateDrawableSize];
}

- (void)nextDrawable
{
    TE_RELEASE(_drawable);
    _drawable = [_metalLayer nextDrawable];
}

- (id <CAMetalDrawable>)currentDrawable
{
    return _drawable;
}

- (id <MTLTexture>) colorTexture
{
    return _drawable.texture;
}

- (id <MTLTexture>) depthTexture
{
    return _depthTexture;
}

@end
