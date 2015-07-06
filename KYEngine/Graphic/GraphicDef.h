#ifndef _GRAPHICDEF_H_
#define _GRAPHICDEF_H_

namespace KY
{
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

	enum BufferType
	{
		BT_Vertex,
		BT_Index,
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
		PT_TriList,
		PT_TriStrip,
	};

	struct BufferParam
	{
		BufferType type;
		BufferCPUAccess access;
		ResourceUsage usage;

		size_t sizeInBytes;
		size_t elemInBytes;
	};

	struct ResourceData
	{
		const uint8 *pData;
		//{@ valid for texture resource
		size_t pitch;
		size_t slicePitch;
		//@}
	};
}
#endif // _GRAPHICDEF_H_