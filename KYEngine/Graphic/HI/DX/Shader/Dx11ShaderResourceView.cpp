#include "stdafx.h"


#include "Dx11ShaderResourceView.h"

#include "Graphic/Graphic.h"

#include "Graphic/HI/DX/Dx11.h"

#include "Graphic/Resource/Resource.h"
#include "Graphic/Resource/Buffer/Buffer.h"
#include "Graphic/Resource/Texture/Texture.h"
#include "Graphic/Resource/Texture/Texture.inl"

#include "Graphic/HI/DX/DX11NameTranslator.h"

#include "Graphic/HI/DX/Buffer/DX11Buffer.h"
#include "Graphic/HI/DX/Texture/Dx11Texture.h"

namespace KY
{
	namespace DX
	{


		static inline ID3D11Resource* get_dx_res(Resource *res)
		{
			switch (res->GetResourceType())
			{
			case ResourceType::ResT_Vertex:
			case ResourceType::ResT_Index:
			case ResourceType::ResT_Const:
				return static_cast<Buffer*>(res)->GetInternal()->GetInternal();
				break;

			case ResourceType::ResT_Texture:
				return static_cast<Texture2D*>(res)->GetInternal()->GetInternal();

			default:
				break;
			}

			BOOST_ASSERT(false && "not support enum");
			return nullptr;
		}
		bool Dx11ShaderResourceView::Init(const SRVParam &param, Resource *res)
		{
			auto dx11 = Graphic::Inst()->GetDx11();
			auto device = dx11->GetDevice();

			D3D11_SHADER_RESOURCE_VIEW_DESC desc = {
				DX::DX11NameTranslator::Inst()->ToDXGI_FORMAT(param.fmt),
				D3D11_SRV_DIMENSION(param.type),
			};

			switch (param.type)
			{
			case SRVParam::SRVType::Buffer:
				static_assert(sizeof(desc.Buffer) == sizeof(param.buffer), "buffer size not correct");
				memcpy(&desc.Buffer, &param.buffer, sizeof(desc.Buffer));
				break;
			case SRVParam::SRVType::Tex1D:
				static_assert(sizeof(desc.Texture1D) == sizeof(param.tex1D), "Texture1D size not correct");
				memcpy(&desc.Texture1D, &param.tex1D, sizeof(desc.Texture1D));
				break;

			case SRVParam::SRVType::Tex2D:
				static_assert(sizeof(desc.Texture2D) == sizeof(param.tex2D), "Texture2D size not correct");
				memcpy(&desc.Texture2D, &param.tex2D, sizeof(desc.Texture2D));
				break;
			case SRVParam::SRVType::Tex1DArray:

			case SRVParam::SRVType::Tex2DArray:
			case SRVParam::SRVType::Tex2DMS:
			case SRVParam::SRVType::Tex2DMSArray:
			case SRVParam::SRVType::Tex3D:
			case SRVParam::SRVType::TexCube:
			case SRVParam::SRVType::BufferEx:

			default:
				break;
			}

			return SUCCEEDED(device->CreateShaderResourceView(get_dx_res(res), &desc, &mInternal));
		}
	}
}
