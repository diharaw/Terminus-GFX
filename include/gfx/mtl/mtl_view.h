#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import <MetalKit/MetalKit.h>

@interface MetalView : NSView


- (id) initWithDevice:(id <MTLDevice>) device withFrame:(CGRect)frame withWindow:(NSWindow*)window;
- (void)     nextDrawable;
- (id <MTLTexture>)          colorTexture;
- (id <MTLTexture>)          depthTexture;
- (id <CAMetalDrawable>)     currentDrawable;
- (CAMetalLayer*)            metalLayer;

@end
