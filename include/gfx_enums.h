#pragma once

namespace ShaderType
{
    enum
    {
        VERTEX		 = 0,
        FRAGMENT	 = 1,
        GEOMETRY	 = 2,
        TESS_CONTROL = 3,
        TESS_EVAL	 = 4,
        COMPUTE		 = 5
    };
};

namespace DepthTest
{
    enum
    {
        DISABLE = 0,
        ENABLE  = 1
    };
};

namespace PrimitiveType
{
    enum
    {
        POINTS         = 0,
        TRIANGLES      = 1,
        TRIANGLE_STRIP = 2,
        LINES          = 3,
        LINE_STRIP     = 4,
		PATCHES		   = 5
    };
};

namespace CullMode
{
    enum
    {
        FRONT          = 0,
        BACK           = 1,
        FRONT_AND_BACK = 2,
        NONE           = 3
    };
};

namespace FillMode
{
    enum
    {
        SOLID     = 0,
        WIREFRAME = 1
    };
};

namespace StencilOperation
{
    enum
    {
        KEEP     = 0,
        ZERO     = 1,
        REPLACE  = 2,
        INCR_SAT = 3,
        DECR_SAT = 4,
        INVERT   = 5,
        INCR     = 6,
        DECR     = 7
    };
};

namespace ComparisonFunction
{
    enum
    {
        NEVER         = 0,
        LESS          = 1,
        EQUAL         = 2,
        LESS_EQUAL    = 3,
        GREATER       = 4,
        NOT_EQUAL     = 5,
        GREATER_EQUAL = 6,
        ALWAYS        = 7
    };
};

namespace GraphicsCommandType
{
    enum
    {
        Draw                  = 0,
        DrawIndexed           = 1,
        DrawIndexedBaseVertex = 2,
        BindTexture           = 3,
        BindSamplerState      = 4,
        BindRasterizerState   = 5,
        BindDepthStencilState = 6,
        BindVertexArray       = 7,
        BindFramebuffer       = 8,
        BindUniformBuffer     = 9,
        CopyUniformData       = 10
    };
};

namespace ClearTarget
{
    enum
    {
        COLOR   = 1,
        DEPTH   = 2,
        STENCIL = 4,
        ALL     = COLOR | DEPTH | STENCIL
    };
};

namespace TextureType
{
	enum
	{
		TEXTURE1D = 0,
		TEXTURE2D = 1,
		TEXTURE3D = 2,
		TEXTURECUBE = 3,
		TEXTURECUBE_POSITIVE_X = TEXTURECUBE + 1,
		TEXTURECUBE_NEGATIVE_X = TEXTURECUBE + 2,
		TEXTURECUBE_POSITIVE_Y = TEXTURECUBE + 3,
		TEXTURECUBE_NEGATIVE_Y = TEXTURECUBE + 4,
		TEXTURECUBE_POSITIVE_Z = TEXTURECUBE + 5,
		TEXTURECUBE_NEGATIVE_Z = TEXTURECUBE + 6
	};
};

namespace CubeMapFaces
{
	enum
	{
		POSITIVE_X = 0,
		NEGATIVE_X = 1,
		POSITIVE_Y = 2,
		NEGATIVE_Y = 3,
		POSITIVE_Z = 4,
		NEGATIVE_Z = 5
	};
};

namespace TextureWrapMode
{
    enum
    {
        REPEAT          = 0,
        MIRRORED_REPEAT = 1,
        CLAMP_TO_EDGE   = 2,
        CLAMP_TO_BORDER = 3
    };
};

namespace TextureFormat
{
    enum
    {
		// @TODO: Add compressed formats
        R32G32B32_FLOAT    = 0,
        R32G32B32A32_FLOAT = 1,
        R32G32B32_UINT     = 2,
        R32G32B32A32_UINT  = 3,
        R32G32B32_INT      = 4,
        R32G32B32A32_INT   = 5,
		R16G16_FLOAT	   = 6,
        R16G16B16_FLOAT    = 7,
        R16G16B16A16_FLOAT = 8,
        R16G16B16_UINT     = 9,
        R16G16B16A16_UINT  = 10,
        R16G16B16_INT      = 11,
        R16G16B16A16_INT   = 12,
        R8G8B8_UNORM       = 13,
        R8G8B8A8_UNORM     = 14,
        R8G8B8_UNORM_SRGB  = 15,
        R8G8B8A8_UNORM_SRGB= 16,
        R8G8B8_SNORM       = 17,
        R8G8B8A8_SNORM     = 18,
        R8G8B8_INT         = 19,
        R8G8B8A8_INT       = 20,
        R8G8B8_UINT        = 21,
        R8G8B8A8_UINT      = 22,
		R8_UNORM		   = 23,
		R8_SNORM		   = 24,
        D32_FLOAT_S8_UINT  = 25,
        D24_FLOAT_S8_UINT  = 26,
        D16_FLOAT          = 27,
		R32G32_FLOAT	   = 28,
		R16_FLOAT		   = 29
    };
};

namespace TextureFilteringMode
{
    enum
    {
        LINEAR                = 0,
        NEAREST               = 1,
        LINEAR_ALL            = 2,
        NEAREST_ALL           = 3,
        ANISOTROPIC_ALL       = 4,
        LINEAR_MIPMAP_NEAREST = 5,
        NEAREST_MIPMAP_LINEAR = 6,
    };
};

namespace BlendOp
{
	enum
	{
		ADD				 = 0,
		SUBTRACT		 = 1,
		REVERSE_SUBTRACT = 2,
		MIN				 = 3,
		MAX				 = 4
	};
};

namespace BlendFunc
{
	enum
	{
		ZERO					 = 0,
		ONE						 = 1,
		SRC_COLOR				 = 2,
		ONE_MINUS_SRC_COLOR		 = 3,
		DST_COLOR				 = 4,
		ONE_MINUS_DST_COLOR		 = 5,
		SRC_ALPHA				 = 6,
		ONE_MINUS_SRC_ALPHA		 = 7,
		DST_ALPHA				 = 8,
		ONE_MINUS_DST_ALPHA		 = 9,
		CONSTANT_COLOR			 = 10,
		ONE_MINUS_CONSTANT_COLOR = 11,
		CONSTANT_ALPHA			 = 12,
		ONE_MINUS_CONSTANT_ALPHA = 13,
		SRC_ALPHA_SATURATE		 = 14,
		SRC1_COLOR				 = 15,
		ONE_MINUS_SRC1_COLOR	 = 16,
		SRC1_ALPHA				 = 17,
		ONE_MINUS_SRC1_ALPHA	 = 18
	};
};

namespace BufferType
{
    enum
    {
        VERTEX  = 0,
        INDEX   = 1,
        UNIFORM = 2,
        APPEND  = 3,
        QUERY   = 4
    };
};

namespace BufferUsageType
{
    enum
    {
        STATIC  = 0,
        DYNAMIC = 1,
        STREAM  = 2
    };
};

namespace BufferMapType
{
    enum
    {
        READ = 0,
        WRITE,
        READ_WRITE
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
