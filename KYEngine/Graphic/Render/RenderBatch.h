#pragma once
#include "Graphic/GraphicDef.h"
#include "Common/BaseTypes.h"
#include "Graphic/Render/BufferRenderProxy.h"

namespace KY
{
	class VertexBuffer;
	class IndexBuffer;
	class Buffer;
	class Material;

	//class RenderElement
	//{
	//public:
	//	RenderElement()
	//		: mMinVertexBufferIdx(0)
	//		, mMaxVertexBufferIdx(0)
	//		, mMinIndexBufferIdx(0)
	//		, mMaxIndexBufferIdx(0)
	//		, mConstBuffer(nullptr)
	//	{
	//	}
	//	uint32 mMinVertexBufferIdx;
	//	uint32 mMaxVertexBufferIdx;
	//	uint32 mMinIndexBufferIdx;
	//	uint32 mMaxIndexBufferIdx;
	//};

	class RenderBatch
	{
	public:
		RenderBatch()
			: mBufferProxy(nullptr)
			, mMaterial(nullptr)
			, mPriType(PrimitiveType::PT_Unknown)
		{}

		BufferRenderProxy	*mBufferProxy;
		Material			*mMaterial;

		PrimitiveType		mPriType;

		//std::vector<RenderElement>	mRenderElems;
	};

	using RenderBatchVec = std::vector<RenderBatch>;
}