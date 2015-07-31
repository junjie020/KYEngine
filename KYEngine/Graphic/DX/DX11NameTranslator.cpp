#include "stdafx.h"
#include "DX11NameTranslator.h"

namespace KY
{
	namespace DX
	{
		D3D11_USAGE DX11NameTranslator::ToD3DUsage(ResourceUsage usage) const
		{
			switch (usage)
			{
			case RU_Default:
				return D3D11_USAGE_DEFAULT;
			case RU_Immutable:
				return D3D11_USAGE_IMMUTABLE;
			case RU_Dynamic:
				return D3D11_USAGE_DYNAMIC;
			case RU_Stage:
				return D3D11_USAGE_STAGING;
			default:
				BOOST_ASSERT(false && "invalid enum");
				return D3D11_USAGE(-1);
			}
		}

		DXGI_FORMAT DX11NameTranslator::ToDXGI_FORMAT(TexFormat tf) const
		{
			return DXGI_FORMAT(tf);
		}

		D3D11_BIND_FLAG DX11NameTranslator::ToBingFlag(BufferType type) const
		{
			D3D11_BIND_FLAG flags[] = { D3D11_BIND_VERTEX_BUFFER, D3D11_BIND_INDEX_BUFFER, D3D11_BIND_CONSTANT_BUFFER, };
			BOOST_ASSERT(COUNT_OF(flags) > type);
			return flags[type];
		}

	}


}