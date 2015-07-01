#include "stdafx.h"
#include "DX11Buffer.h"
#include "Common/CommonUtils.h"
namespace KY
{
	namespace DX
	{
		DX11Buffer::DX11Buffer(const BufferParam &param)
			: mParam(param)
			, mBuffer(nullptr)
		{}

		DX11Buffer::~DX11Buffer()
		{
			SafeRelease(mBuffer);
		}
	}
}