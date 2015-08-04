#ifndef _GRAPHICDEF_H_
#define _GRAPHICDEF_H_

namespace KY
{
	enum BufferType
	{
		BT_Vertex = 0,
		BT_Index,
		BT_Const,
	};
	enum BufferCPUAccess
	{
		BA_None = 0,
		BA_Read = 0x01,
		BA_Write = 0x02,
	};

	enum ResourceUsage
	{
		RU_Default = 0,
		RU_Immutable,
		RU_Dynamic,
		RU_Stage,
	};

	enum PrimitiveType
	{
		PT_Unknown = -1,
		PT_Point = 0,
		PT_LineList,
		PT_LineStrip,
		PT_TriList,
		PT_TriStrip,

		PT_LineList_ADJ,		
		PT_LineStrip_ADJ,
		PT_TriList_ADJ,
		PT_TriStrip_ADJ,		

		PT_ControlPointBeg,
		PT_ControlPointEnd = PT_ControlPointBeg + 32,
	};

	enum ShaderType
	{
		ShdrT_Vertex = 0,
		ShdrT_Hull,
		ShdrT_Domain,
		ShdrT_Geometry,
		ShdrT_Pixel,
		ShdrT_Count,
	};

	enum TexFormat
	{
		TF_UNKNOWN = 0,
		TF_R32G32B32A32_TYPELESS = 1,
		TF_R32G32B32A32_FLOAT = 2,
		TF_R32G32B32A32_UINT = 3,
		TF_R32G32B32A32_SINT = 4,
		TF_R32G32B32_TYPELESS = 5,
		TF_R32G32B32_FLOAT = 6,
		TF_R32G32B32_UINT = 7,
		TF_R32G32B32_SINT = 8,
		TF_R16G16B16A16_TYPELESS = 9,
		TF_R16G16B16A16_FLOAT = 10,
		TF_R16G16B16A16_UNORM = 11,
		TF_R16G16B16A16_UINT = 12,
		TF_R16G16B16A16_SNORM = 13,
		TF_R16G16B16A16_SINT = 14,
		TF_R32G32_TYPELESS = 15,
		TF_R32G32_FLOAT = 16,
		TF_R32G32_UINT = 17,
		TF_R32G32_SINT = 18,
		TF_R32G8X24_TYPELESS = 19,
		TF_D32_FLOAT_S8X24_UINT = 20,
		TF_R32_FLOAT_X8X24_TYPELESS = 21,
		TF_X32_TYPELESS_G8X24_UINT = 22,
		TF_R10G10B10A2_TYPELESS = 23,
		TF_R10G10B10A2_UNORM = 24,
		TF_R10G10B10A2_UINT = 25,
		TF_R11G11B10_FLOAT = 26,
		TF_R8G8B8A8_TYPELESS = 27,
		TF_R8G8B8A8_UNORM = 28,
		TF_R8G8B8A8_UNORM_SRGB = 29,
		TF_R8G8B8A8_UINT = 30,
		TF_R8G8B8A8_SNORM = 31,
		TF_R8G8B8A8_SINT = 32,
		TF_R16G16_TYPELESS = 33,
		TF_R16G16_FLOAT = 34,
		TF_R16G16_UNORM = 35,
		TF_R16G16_UINT = 36,
		TF_R16G16_SNORM = 37,
		TF_R16G16_SINT = 38,
		TF_R32_TYPELESS = 39,
		TF_D32_FLOAT = 40,
		TF_R32_FLOAT = 41,
		TF_R32_UINT = 42,
		TF_R32_SINT = 43,
		TF_R24G8_TYPELESS = 44,
		TF_D24_UNORM_S8_UINT = 45,
		TF_R24_UNORM_X8_TYPELESS = 46,
		TF_X24_TYPELESS_G8_UINT = 47,
		TF_R8G8_TYPELESS = 48,
		TF_R8G8_UNORM = 49,
		TF_R8G8_UINT = 50,
		TF_R8G8_SNORM = 51,
		TF_R8G8_SINT = 52,
		TF_R16_TYPELESS = 53,
		TF_R16_FLOAT = 54,
		TF_D16_UNORM = 55,
		TF_R16_UNORM = 56,
		TF_R16_UINT = 57,
		TF_R16_SNORM = 58,
		TF_R16_SINT = 59,
		TF_R8_TYPELESS = 60,
		TF_R8_UNORM = 61,
		TF_R8_UINT = 62,
		TF_R8_SNORM = 63,
		TF_R8_SINT = 64,
		TF_A8_UNORM = 65,
		TF_R1_UNORM = 66,
		TF_R9G9B9E5_SHAREDEXP = 67,
		TF_R8G8_B8G8_UNORM = 68,
		TF_G8R8_G8B8_UNORM = 69,
		TF_BC1_TYPELESS = 70,
		TF_BC1_UNORM = 71,
		TF_BC1_UNORM_SRGB = 72,
		TF_BC2_TYPELESS = 73,
		TF_BC2_UNORM = 74,
		TF_BC2_UNORM_SRGB = 75,
		TF_BC3_TYPELESS = 76,
		TF_BC3_UNORM = 77,
		TF_BC3_UNORM_SRGB = 78,
		TF_BC4_TYPELESS = 79,
		TF_BC4_UNORM = 80,
		TF_BC4_SNORM = 81,
		TF_BC5_TYPELESS = 82,
		TF_BC5_UNORM = 83,
		TF_BC5_SNORM = 84,
		TF_B5G6R5_UNORM = 85,
		TF_B5G5R5A1_UNORM = 86,
		TF_B8G8R8A8_UNORM = 87,
		TF_B8G8R8X8_UNORM = 88,
		TF_R10G10B10_XR_BIAS_A2_UNORM = 89,
		TF_B8G8R8A8_TYPELESS = 90,
		TF_B8G8R8A8_UNORM_SRGB = 91,
		TF_B8G8R8X8_TYPELESS = 92,
		TF_B8G8R8X8_UNORM_SRGB = 93,
		TF_BC6H_TYPELESS = 94,
		TF_BC6H_UF16 = 95,
		TF_BC6H_SF16 = 96,
		TF_BC7_TYPELESS = 97,
		TF_BC7_UNORM = 98,
		TF_BC7_UNORM_SRGB = 99,
		TF_FORCE_UINT = 0xffffffff
	};

	enum FillMode
	{
		FM_WireFrame = 0,
		FM_Solid,
	};

	enum CullMode
	{
		CM_None = 0,
		CM_Front,
		CM_Back,
	};

	enum CompareFunc
	{
		CF_Never = 0,
		CF_Less,
		CF_Equal,
		CF_LessEqual,
		CF_Greater,
		CF_NotEqual,
		CF_GreaterEqual,
		CF_Always,
	};

	enum StencilOperation
	{
		StencilOP_Keep = 0,
		StencilOP_Zero,
		StencilOP_Replace,
		StencilOP_Incr_Sat,
		StencilOP_Decr_Sat,
		StencilOP_Invert,
		StencilOP_Incr,
		StencilOP_Decr,
	};

	enum BlendType
	{
		BlendType_Zero = 0,
		BlendType_One,
		BlendType_SrcColor,
		BlendType_InvSrcColor,
		BlendType_SrcAlpha,
		BlendType_InvSrcAlpha,
		BlendType_DestAlpha,
		BlendType_InvDestAlpha,
		BlendType_DestColor,
		BlendType_InvDestColor,
		BlendType_SrcAlphaSat,
		BlendType_BlendFactor,
		BlendType_InvBlendFactor,
		BlendType_Src1Color,
		BlendType_InvSRC1Color,
		BlendType_Src1Alpha,
		BlendType_InvSrc1Alpha,
	};

	enum BlendOperation
	{
		BlendOP_Add = 0,		
		BlendOP_Subtract,
		BlendOP_RevSubtract,
		BlendOP_Min,
		BlendOP_Max,		
	};

	enum RenderTargetColorWirteMask
	{
		RTCW_Red	= 0x01,
		RTCW_Green	= 0x02,
		RTCW_Blue	= 0x04,
		RTCW_Alpha	= 0x08,

		RTCW_All = RTCW_Red | RTCW_Green | RTCW_Blue | RTCW_Alpha,
	};

	struct GraphicInitParam
	{
		uint32 width, height;
		uint32 featureLevel;
		struct SampleDesc
		{
			uint32 count;
			uint32 level;
		};
		SampleDesc sampleDesc;
		HWND hwnd;
	};

	struct BufferParam
	{
		BufferType type;
		BufferCPUAccess access;
		ResourceUsage usage;

		size_t sizeInBytes;
		size_t elemInBytes;
	};

	struct BufferInfo{
		uint32 offset;
		uint32 strides;
		uint32 slotIdx;		
	};

	struct ResourceData
	{
		const uint8 *pData;
		//{@ valid for texture resource
		size_t pitch;
		size_t slicePitch;
		//@}
	};

	struct InputElemDesc
	{
		const char* semanticName;
		uint32		semanticIndex;
		TexFormat	format;
		uint32		inputSlot;
		uint32		alignedByteOffset;
		//D3D11_INPUT_CLASSIFICATION InputSlotClass;
		//UINT InstanceDataStepRate;
	};

	struct RasterizerState
	{
		//{@
		FillMode	fillMode;
		CullMode	cullMode;
		bool		frontCCW;
		//@}

		//{@
		int32		depthBias;
		float		depthBiasClamp;
		float		slopeScaledDepthBias;

		bool		depthClipEnable;
		//@}

		//{@
		bool		scissorEnable;
		bool		multisampleEnable;
		bool		antialiasedLineEnable;
		//@}
	};

	struct DepthStencilState
	{
		DepthStencilState() 
			: depthEnable(true)
			, enableDepthWrite(true)
		{

		}
		//{@
		bool	depthEnable;
		bool	enableDepthWrite;
		CompareFunc depthFunc;
		//@}

		bool	stencilEnable;
		uint8	stencilReadMask;
		uint8	stencilWriteMask;

		struct StencilOpDesc
		{
			StencilOperation	stencilFailOp;
			StencilOperation	stencilDepthFailOp;
			StencilOperation	stencilPassOp;
			CompareFunc			stencilFunc;
		};

		StencilOpDesc frontFaceOp;
		StencilOpDesc backFaceOp;
	};

	struct BlendState
	{
		bool alphaToCoverageEnable;
		bool independentBlendEnable;

		struct RenderTargetBlendDesc
		{
			bool blendEnable;

			struct BlendOpDesc{
				BlendType		src;
				BlendType		dst;
				BlendOperation	op;
			};

			BlendOpDesc clrOpDesc;
			BlendOpDesc alphaOpDesc;

			RenderTargetColorWirteMask		renderTargetWriteMask;
		};

		RenderTargetBlendDesc renderTargetDesc[8];
	};
}
#endif // _GRAPHICDEF_H_