#include "stdafx.h"

#include "Buffer.h"

namespace KY
{
	Buffer::Buffer(ResourceType type)
		: Resource(type)		
	{}

	bool Buffer::Init(const BufferParam &param, const ResourceData &resData)
	{
		mDx11Internal = new DX::DX11Buffer(param, resData);
		return mDx11Internal != nullptr;
	}

	bool Buffer::Map(ResourceMapParam &param)
	{
		return mDx11Internal->Map(param);
	}

	void Buffer::UnMap(uint32 subRes)
	{
		mDx11Internal->UnMap(subRes);
	}

	const BufferParam& Buffer::GetBufferParam() const
	{
		return mDx11Internal->GetBufferParam();
	}

}