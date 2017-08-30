#include "stdafx.h"
#include "DX11Buffer.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"
#include "Graphic/HI/DX/Dx11.h"

#include "Graphic/Graphic.h"

#include "Common/CommonUtils.h"
#include "DebugUtils/TraceUtils.h"

namespace KY
{
	namespace DX
	{
		DX11Buffer::DX11Buffer(const BufferParam &param, const ResourceData &resData)
			: mParam(param)			
		{
			auto device = Graphic::Inst()->GetDx11()->GetDevice();
			D3D11_BUFFER_DESC desc = { 0 };
			desc.BindFlags = DX11NameTranslator::Inst()->ToBingFlag(param.type);
			desc.MiscFlags = DX11NameTranslator::Inst()->ToResMiscFlag(param.miscFlags);
			desc.Usage = DX11NameTranslator::Inst()->ToUsage(param.usage);

			if (QueryBit(uint8(ResourceCPUAccess::Read), uint8(param.access)))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
			if (QueryBit(uint8(ResourceCPUAccess::Write), uint8(param.access)))
				desc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;

			desc.ByteWidth = param.sizeInBytes;	
			desc.StructureByteStride = param.byteStrideForStructureBuffer;

			D3D11_SUBRESOURCE_DATA data = { resData.pData, resData.pitch, resData.slicePitch };
			
			if (FAILED(device->CreateBuffer(&desc, resData.pData ? &data : nullptr, &mInternal)))
			{
				DebugOutline("info vertex buffer failed");
			}
		}

		bool DX11Buffer::Map(ResourceMapParam &param)
		{
			BOOST_ASSERT(mInternal);

			auto context = Graphic::Inst()->GetDx11()->GetDeviceContext();

			
			D3D11_MAPPED_SUBRESOURCE subres = { 0 };

			static_assert(sizeof(subres) == sizeof(param.mapData), "incompaitable size for D3D11_MAPPED_SUBRESOURCE with ResourceMapParam::MapData");
			auto result = context->Map(mInternal, param.subRes,
									DX11NameTranslator::Inst()->TopMap(param.mapType), 
									param.waitWhenGpuBusy ? D3D11_MAP_FLAG_DO_NOT_WAIT : 0, &subres);
			if (SUCCEEDED(result))
			{
				param.mapData = *(reinterpret_cast<ResourceMapParam::MapData*>(&subres));				
				return true;
			}

			// print_dx_error()
			return false;
		}

		void DX11Buffer::UnMap(uint32 subRes)
		{
			auto context = Graphic::Inst()->GetDx11()->GetDeviceContext();
			context->Unmap(mInternal, subRes);
		}

	}
}