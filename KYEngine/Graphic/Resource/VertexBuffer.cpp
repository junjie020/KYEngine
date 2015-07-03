#include "stdafx.h"
#include "VertexBuffer.h"
#include "Graphic/DX/Buffer/DX11VertexBuffer.h"
namespace KY
{
	VertexBuffer::VertexBuffer()
		:mBuffer(nullptr)
	{

	}

	VertexBuffer::~VertexBuffer()
	{
		SafeDelete(mBuffer);
	}

	bool VertexBuffer::Create(const BufferParam &param, const ResourceData &resData)
	{
		mBuffer = new DX::DX11VertexBuffer(param, resData);

		return mBuffer != nullptr;
	}

}