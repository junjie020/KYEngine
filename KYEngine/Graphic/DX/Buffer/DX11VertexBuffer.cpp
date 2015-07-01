#include "stdafx.h"
#include "DX11VertexBuffer.h"

#include "Graphic/Graphic.h"
#include "DebugUtils/TraceUtils.h"

#include "Graphic/DX/Dx11.h"
#include "Graphic/DX/DX11NameTranslator.h"

#include "Common/CommonUtils.h"

namespace KY
{
	namespace DX
	{
		DX11VertexBuffer::DX11VertexBuffer(const BufferParam &param, const ResourceData &resData)
			: DX11Buffer(param)
		{
			auto device = Graphic::Inst()->GetDx11()->GetDevice();
			D3D11_BUFFER_DESC desc = { 0 };
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.Usage = DX11NameTranslator::Inst()->ToD3DUsage(param.usage);
			
			if (QueryBit(BA_Read, param.access))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
			if (QueryBit(BA_Write, param.access))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;

			desc.ByteWidth				= param.sizeInBytes;
			desc.StructureByteStride	= param.elemInBytes;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem			= resData.pData;
			data.SysMemPitch		= resData.pitch;
			data.SysMemSlicePitch	= resData.slicePitch;
			if (FAILED(device->CreateBuffer(&desc, &data, &mBuffer)))
			{
				DebugOutline("info vertex buffer failed");
			}
		}

		DX::DX11VertexBuffer::~DX11VertexBuffer()
		{

		}
	}
}