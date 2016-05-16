#include "stdafx.h"
#include "DX11NameTranslator.h"

#include "Graphic/Resource/Resource.h"
#include "Graphic/Resource/Buffer/Buffer.h"
#include "Graphic/Resource/Texture/Texture.h"
#include "Graphic/Resource/Texture/Texture.inl"

#include "Graphic/HI/DX/Buffer/DX11Buffer.h"
#include "Graphic/HI/DX/Texture/Dx11Texture.h"

namespace KY
{
	namespace DX
	{

		ID3D11Resource* DX11NameTranslator::ToD3DResource(Resource *res) const
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

		D3D11_PRIMITIVE_TOPOLOGY DX11NameTranslator::ToPrimitiveTopology(PrimitiveType type) const
		{
			D3D11_PRIMITIVE_TOPOLOGY d3dpri[] = {				
				D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
				D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
				D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
				D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
				D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
				D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
				D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST
			};
				
			BOOST_ASSERT(COUNT_OF(d3dpri) > uint32(type));
			return d3dpri[type];
		}
	}


}