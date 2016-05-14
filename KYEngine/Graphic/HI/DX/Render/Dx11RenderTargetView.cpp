#include "stdafx.h"

#include "Dx11RenderTargetView.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"

#include "Graphic/Graphic.h"
#include "Graphic/HI/DX/Dx11.h"

namespace KY
{
	namespace DX
	{
		bool Dx11RenderTargetView::Init(const RTVParam& param, Resource *res)
		{
			static_assert(sizeof(RTVParam::Tex1D) == sizeof(D3D11_TEX1D_RTV), "tex1D is not equal");
			static_assert(sizeof(RTVParam::Tex2D) == sizeof(D3D11_TEX1D_RTV), "tex2D is not equal");

			D3D11_RENDER_TARGET_VIEW_DESC desc = {
				DX::DX11NameTranslator::Inst()->ToDXGI_FORMAT(param.fmt),
				D3D11_RTV_DIMENSION(param.type),
			};

			switch (param.type)
			{
			case RTVParam::RTVType::Tex2D:
				break;
			case RTVParam::RTVType::Buffer:
			case RTVParam::RTVType::Tex1D:
			case RTVParam::RTVType::Tex1DArray:
			
			case RTVParam::RTVType::Tex2DArray:
			case RTVParam::RTVType::Tex2DMS:
			case RTVParam::RTVType::Tex2DMSArray:
			case RTVParam::RTVType::Tex3D:
			case RTVParam::RTVType::Unknown:
			default:
				BOOST_ASSERT(false && "not implement right now");
			}

			auto dx11 = Graphic::Inst()->GetDx11();
			auto device = dx11->GetDevice();

			return SUCCEEDED(device->CreateRenderTargetView(DX::DX11NameTranslator::Inst()->ToD3DResource(res), &desc, &mInternal));
		}
	}
}