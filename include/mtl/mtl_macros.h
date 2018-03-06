

#define TE_OBJC_CAST(TYPE, OBJECT) (__bridge id<TYPE>)OBJECT
#define TE_OBJC_REG_CAST(TYPE, OBJECT) (__bridge TYPE)OBJECT

#define TE_MTL_DEVICE(x) TE_OBJC_CAST(MTLDevice, x)
#define TE_MTL_COMMAND_BUFFER(x) TE_OBJC_CAST(MTLCommandBuffer, x)
#define TE_MTL_COMMAND_QUEUE(x) TE_OBJC_CAST(MTLCommandQueue, x)

#ifdef _WIN64
    #define TE_PLATFORM_WIN64
#elif _WIN32
    #define TE_PLATFORM_WIN32
#elif __APPLE__
#include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        #define TE_PLATFORM_IPHONE_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define TE_PLATFORM_IPHONE
    #else
        #define TARGET_OS_OSX 1
        #define TE_PLATFORM_MACOS
    #endif
#elif __ANDROID__
    #define TE_PLATFORM_ANDROID
#elif __linux
    #define TE_PLATFORM_LINUX
#elif __unix
    #define TE_PLATFORM_UNIX
#elif __posix
    #define TE_PLATFORM_POSIX
#endif

#define TE_RELEASE(object) [object release]; object = nil
