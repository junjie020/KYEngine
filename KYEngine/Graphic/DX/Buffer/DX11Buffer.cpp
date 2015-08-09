#include "stdafx.h"
#include "DX11Buffer.h"
#include "Graphic/DX/DX11NameTranslator.h"
#include "Graphic/DX/Dx11.h"

#include "Graphic/Graphic.h"

#include "Common/CommonUtils.h"
#include "DebugUtils/TraceUtils.h"

namespace KY
{
	namespace DX
	{
		DX11Buffer::DX11Buffer(const BufferParam &param, const ResourceData &resData)
			: mParam(param)
			, mBuffer(nullptr)
		{
			auto device = Graphic::Inst()->GetDx11()->GetDevice();
			D3D11_BUFFER_DESC desc = { 0 };
			desc.BindFlags = DX11NameTranslator::Inst()->ToBingFlag(param.type);

			desc.Usage = DX11NameTranslator::Inst()->ToUsage(param.usage);

			if (QueryBit(BA_Read, param.access))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
			if (QueryBit(BA_Write, param.access))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;

			desc.ByteWidth = param.sizeInBytes;
			desc.StructureByteStride = 0;// param.elemInBytes;

			D3D11_SUBRESOURCE_DATA data = { resData.pData, resData.pitch, resData.slicePitch };
			
			if (FAILED(device->CreateBuffer(&desc, &data, &mBuffer)))
			{
				DebugOutline("info vertex buffer failed");
			}
		}

		DX11Buffer::~DX11Buffer()
		{
			SafeRelease(mBuffer);
		}
	}
}