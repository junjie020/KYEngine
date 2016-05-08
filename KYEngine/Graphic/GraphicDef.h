#ifndef _GRAPHICDEF_H_
#define _GRAPHICDEF_H_

namespace KY
{

#define MAX_SAMPLER_STATE_NUM 16

	enum FeatureLevel : uint8
	{
		FL_Unknown = uint8(-1),
		FL_9_1	= 0,
		FL_9_2,
		FL_9_3,
		FL_10_0,
		FL_10_1,
		FL_11_0,
		FL_11_1,
	};
	enum ResourceType : uint8
	{
		ResT_Vertex = 0,
		ResT_Index,
		ResT_Const,

		ResT_Shader,

		ResT_Texture,		
	};
	enum ResourceCPUAccess : uint8
	{
		BA_None = 0,
		BA_Read = 0x01,
		BA_Write = 0x02,
	};

	enum ResourceMapType : uint8
	{
		ResMT_Read = 0,
		ResMT_Write,
		ResMT_ReadWrite,

		ResMT_WriteDiscard,
		ResMT_WriteNoOverwrite,
	};

	enum ResourceUsage : uint8
	{
		RU_Default = 0,
		RU_Immutable,
		RU_Dynamic,
		RU_Stage,
	};

	enum PrimitiveType : uint16
	{
		PT_Unknown = uint16(-1),
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

	enum ShaderType : uint8
	{
		ShdrT_Vertex = 0,
		ShdrT_Hull,
		ShdrT_Domain,
		ShdrT_Geometry,
		ShdrT_Pixel,
		ShdrT_Count,
	};

	enum TexFormat : uint32
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

	enum FillMode : uint8
	{
		FM_WireFrame = 0,
		FM_Solid,
	};

	enum CullMode : uint8
	{
		CM_None = 0,
		CM_Front,
		CM_Back,
	};

	enum CompareFunc : uint8
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

	enum StencilOperation : uint8
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

	enum BlendType : uint8
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

	enum BlendOperation : uint8
	{
		BlendOP_Add = 0,		
		BlendOP_Subtract,
		BlendOP_RevSubtract,
		BlendOP_Min,
		BlendOP_Max,		
	};

	enum RenderTargetColorWirteMask : uint8
	{
		RTCW_Red	= 0x01,
		RTCW_Green	= 0x02,
		RTCW_Blue	= 0x04,
		RTCW_Alpha	= 0x08,

		RTCW_All = RTCW_Red | RTCW_Green | RTCW_Blue | RTCW_Alpha,
	};

#define MAX_SLOT_ELEM_IDX 4

	enum SlotIndex : uint16
	{
		SI_Position		= 0,
		SI_Normal,
		SI_Tangent,
		SI_Binormal,
		SI_BlendWeight,
		SI_BlendIndices,
		SI_Color,
		SI_Texcoord = SI_Color + MAX_SLOT_ELEM_IDX,

		SI_Unknown = SI_Texcoord + MAX_SLOT_ELEM_IDX,
	};

	enum BindFlag : uint16
	{
		BF_VertexBuffer = 0x01,
		BF_IndexBuffer = 0x02,
		BF_ConstBuffer = 0x04,
		BF_ShaderResource = 0x08,
		BF_StreamOutput = 0x10,
		BF_RenderTarget = 0x20,
		BF_DepthStencil = 0x40,
		BF_UnorderedAccess = 0x80,		
		/*D3D11_BIND_DECODER = 0x200L,
		D3D11_BIND_VIDEO_ENCODER = 0x400L*/
	};

	enum FilterType : uint16
	{
		FT_MinMagMip_Point = 0,
		FT_MinMag_Point_Mip_Linear = 0x01,
		FT_Min_Point_Mag_Linear_Mip_Point = 0x04,
		FT_Min_Point_MagMip_Linear = 0x05,
		FT_Min_Linear_MagMip_Point = 0x10,
		FT_Min_Linear_Mag_Point_Mip_Linear = 0x11,
		FT_MinMag_Linear_Mip_Point = 0x14,
		FT_MinMagMip_Linear = 0x15,
		FT_Anisotropic = 0x55,

		FT_Comparision_MinMagMip_Point = 0x80,
		FT_Comparision_MinMag_Point_Mip_Linear = 0x81,
		FT_Comparision_Min_Point_Mag_Linear_Mip_Point = 0x84,
		FT_Comparision_Min_Point_MagMip_Linear = 0x85,
		FT_Comparision_Min_Linear_MagMip_Point = 0x90,
		FT_Comparision_Min_Linear_Mag_Point_Mip_Linear = 0x91,
		FT_Comparision_MinMag_Linear_Mip_Point = 0x94,
		FT_Comparision_MinMagMip_Linear = 0x95,
		FT_Comparision_Anisotropic = 0xd5,
		
		FT_MinNum_MinMagMip_Point = 0x100,
		FT_MinNum_MinMag_Point_Mip_Linear = 0x101,
		FT_MinNum_Min_Point_Mag_Linear_Mip_Point = 0x104,
		FT_MinNum_Min_Point_MagMip_Linear = 0x105,
		FT_MinNum_Min_Linear_MagMip_Point = 0x110,
		FT_MinNum_Min_Linear_Mag_Point_Mip_Linear = 0x111,
		FT_MinNum_MinMag_Linear_Mip_Point = 0x114,
		FT_MinNum_MinMagMip_Linear = 0x115,
		FT_MinNum_Anisotropic = 0x155,


		FT_MaxNum_MinMagMip = 0x180,

		FT_MaxNum_MinMag_Point_Mip_Linear = 0x181,
		FT_MaxNum_Min_Point_Mag_Linear_Mip_Point = 0x184,
		FT_MaxNum_Min_Point_MagMip_Linear = 0x185,
		FT_MaxNum_Min_Linear_MagMip_Point = 0x190,
		FT_MaxNum_Min_Linear_Mag_Point_Mip_Linear = 0x191,
		FT_MaxNum_MinMag_Linear_Mip_Point = 0x194,
		FT_MaxNum_MinMagMip_Linear = 0x195,
		FT_MaxNum_Anisotropic = 0x1d5,
	} ;

	enum AddressMode : uint8
	{
		AddrM_Wrap = 1,
		AddrM_Mirror,
		AddrM_Clamp,
		AddrM_Border,
		AddrM_MirrorOnce,		
	};

	struct GraphicInitParam
	{
		uint32 width, height;		
		struct SampleDesc
		{
			uint32 count;
			uint32 level;
		};
		SampleDesc sampleDesc;

		//{@	only dx
		FeatureLevel featureLevel;
		HWND hwnd;
		//@}

		bool windowed;
	};

	struct BufferParam
	{
		ResourceType type;
		ResourceCPUAccess access;
		ResourceUsage usage;

		uint32 sizeInBytes;
		uint32 byteStrideForStructureBuffer;
	};

	struct TextureParam 
	{
		struct SampleDesc {
			uint32 count;
			uint32 quality;
		};

		uint32				mipmap;
		uint32				arraySize;

		BindFlag			bind;
		ResourceCPUAccess	access;
		ResourceUsage		usage;		
		TexFormat			fmt;

		SampleDesc			sample;
		uint32				msic;
	};

	struct Texture1DParam : public TextureParam
	{
		uint32 width;
	};

	struct Texture2DParam : public TextureParam
	{
		uint32 width, height;
	};


	//{@
	namespace SRVDataType
	{
		struct Buffer {
			union  
			{
				uint32 idx;
				uint32 offset;
			};

			union 
			{
				uint32 numElms;
				uint32 elemWidth;
			};
		};

		struct Tex1D {
			uint32 mostDetailedMip;
			uint32 mipLevels;
		};

		struct Tex2D {
			uint32 mostDetailedMip;
			uint32 mipLevels;
		};
	}

	struct SRVParam
	{
		enum class SRVType {
			Buffer,
			Tex1D,
			Tex1DArray,
			Tex2D,
			Tex2DArray,
			Tex2DMS,
			Tex2DMSArray,
			Tex3D,
			TexCube,
			TexCubeArray,
			BufferEx,
		};

		TexFormat fmt;
		SRVType type;
		union  
		{
			SRVDataType::Buffer buffer;
			SRVDataType::Tex1D tex1D;
			SRVDataType::Tex2D tex2D;
		};
	};
	//@}	 

	struct ResourceMapParam
	{
		uint32			subRes;
		ResourceMapType mapType;
		struct MapData{
			uint8* data;
			uint32 rowPitch;
			uint32 depthPitch;
		};
		MapData			mapData;

		bool			waitWhenGpuBusy;

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
		uint32		instanceDataStepRate;
		bool		instanceData;
	};

	struct RasterizerState
	{
		RasterizerState()
			: fillMode(FM_Solid)
			, cullMode(CM_Back)
			, frontCCW(false)
			, depthBias(0)
			, slopeScaledDepthBias(0.0f)
			, depthBiasClamp(0.0f)
			, depthClipEnable(true)
			, scissorEnable(false)
			, multisampleEnable(false)
			, antialiasedLineEnable(false)
		{

		}
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
			, depthFunc(CF_Less)
			, stencilEnable(false)
			, stencilReadMask(0xff)
			, stencilWriteMask(0xff)			
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
			StencilOpDesc()
				: stencilFailOp(StencilOP_Keep)
				, stencilDepthFailOp(StencilOP_Keep)
				, stencilPassOp(StencilOP_Keep)
				, stencilFunc(CF_Always)
			{}
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
		BlendState() 
			: alphaToCoverageEnable(false)
			, independentBlendEnable(false)
		{

		}
		bool alphaToCoverageEnable;
		bool independentBlendEnable;

		struct RenderTargetBlendDesc
		{
			RenderTargetBlendDesc()
				: blendEnable(false)
				, renderTargetWriteMask(RTCW_All)
			{}

			bool blendEnable;

			struct BlendOpDesc{
				BlendOpDesc()
					: src(BlendType_One)
					, dst(BlendType_Zero)
					, op(BlendOP_Add)
				{}

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

	struct SamplerState
	{
		SamplerState()
			: filter(FT_MinMagMip_Linear)
			, addrU(AddrM_Clamp)
			, addrV(AddrM_Clamp)
			, addrW(AddrM_Clamp)
			, mipLODBias(0)
			, maxAnisotropy(1)
			, compFunc(CF_Never)
			, minLOD(-FLT_MAX)
			, maxLOD(FLT_MAX)
		{
			borderClr[0] = borderClr[1] = borderClr[2] = borderClr[3];
		}

		FilterType filter;

		AddressMode addrU;
		AddressMode addrV;
		AddressMode addrW;

		float mipLODBias;
		uint32 maxAnisotropy;
		CompareFunc compFunc;

		float borderClr[4];
		float minLOD;
		float maxLOD;
	};


}
#endif // _GRAPHICDEF_H_