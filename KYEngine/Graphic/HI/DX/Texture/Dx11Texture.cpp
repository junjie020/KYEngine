#include "stdafx.h"

#include "Dx11Texture.h"

#include "Graphic/Graphic.h"
#include "Graphic/HI/DX/Dx11.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"

#include "Graphic/Resource/Texture/TextureAssertLoader.h"

namespace KY
{
	bool Dx11Texture2D::Create(const Texture2DParam &param, const ResourceData &resData)
	{
		auto dx11 = Graphic::Inst()->GetDx11();
		BOOST_ASSERT(dx11);

		auto device = dx11->GetDevice();

		const DXGI_SAMPLE_DESC sample = { param.sample.count, param.sample.quality };
		const D3D11_TEXTURE2D_DESC desc = {
			param.width, param.height, param.mipmap,
			param.arraySize,

			DX::DX11NameTranslator::Inst()->ToDXGI_FORMAT(param.fmt),
			sample,

			DX::DX11NameTranslator::Inst()->ToUsage(param.usage),

			uint32(DX::DX11NameTranslator::Inst()->ToBingFlag(param.bind)),
			uint32(DX::DX11NameTranslator::Inst()->ToCPUAccessFlag(param.access)),
			param.msic
		};

		const D3D11_SUBRESOURCE_DATA data = { resData.pData, resData.pitch, resData.slicePitch };
	
		return (SUCCEEDED(device->CreateTexture2D(&desc, data.pSysMem ? &data : nullptr, &mTexture)));
	}

	bool Dx11Texture2D::Create(const TextureParam &param, class TextureAssertLoader *loader)
	{
		BOOST_ASSERT(loader);

		Texture2DParam tex2dParam;
		static_assert(sizeof(tex2dParam) > sizeof(param), "Texture2DParam must derive from TextureParam");

		memcpy(&tex2dParam, &param, sizeof(param));

		tex2dParam.width = loader->Width();
		tex2dParam.height = loader->Height();

		ResourceData data = {
			loader->GetData(),
			0, 0,
		};

		return Create(tex2dParam, data);
	}

}
