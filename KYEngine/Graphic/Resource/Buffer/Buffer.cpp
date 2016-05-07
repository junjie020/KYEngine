#include "stdafx.h"

#include "Buffer.h"

namespace KY
{
	Buffer::Buffer(ResourceType type)
		: Resource(type)
		, mBuffer(nullptr)
	{}

	Buffer::~Buffer()
	{
		SafeDelete(mBuffer);
	}

	bool Buffer::Create(const BufferParam &param, const ResourceData &resData)
	{
		mBuffer = new DX::DX11Buffer(param, resData);
		return mBuffer != nullptr;
	}

	bool Buffer::Map(ResourceMapParam &param)
	{
		return mBuffer->Map(param);
	}

	void Buffer::UnMap(uint32 subRes)
	{
		mBuffer->UnMap(subRes);
	}

	const BufferParam& Buffer::GetBufferParam() const
	{
		return mBuffer->GetBufferParam();
	}


}