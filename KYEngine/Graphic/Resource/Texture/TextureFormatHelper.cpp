#include "stdafx.h"


#include "TextureFormatHelper.h"
namespace KY
{
	
	void TextureFormatHelper::Init()
	{
#define INSERT_ELEM(_TYPE, _SIZE, _ELEM_NUM_IN_TYPE) mData.insert(std::make_pair(_TYPE, Format(_SIZE, _ELEM_NUM_IN_TYPE)))
		INSERT_ELEM(TF_R32G32B32A32_TYPELESS, 4 * 4, 4);
		
		INSERT_ELEM(TF_R32G32B32A32_FLOAT, 4 * 4, 4);
		INSERT_ELEM(TF_R32G32B32A32_UINT, 4 * 4, 4);
		INSERT_ELEM(TF_R32G32B32A32_SINT,  4 * 4, 4);
		INSERT_ELEM(TF_R32G32B32_TYPELESS, 4 * 3, 3);
		INSERT_ELEM(TF_R32G32B32_FLOAT, 4 * 3, 3);
		INSERT_ELEM(TF_R32G32B32_UINT, 4 * 3, 3);
		INSERT_ELEM(TF_R32G32B32_SINT, 4 * 3, 3);
		INSERT_ELEM(TF_R16G16B16A16_TYPELESS, 2 * 4, 4);
		INSERT_ELEM(TF_R16G16B16A16_FLOAT, 2 * 4, 4);
		INSERT_ELEM(TF_R16G16B16A16_UNORM, 2 * 4, 4);
		INSERT_ELEM(TF_R16G16B16A16_UINT, 2 * 4, 4);
		INSERT_ELEM(TF_R16G16B16A16_SNORM, 2 * 4, 4);
		INSERT_ELEM(TF_R16G16B16A16_SINT, 2 * 4, 4);
		INSERT_ELEM(TF_R32G32_TYPELESS, 4 * 2, 2);
		INSERT_ELEM(TF_R32G32_FLOAT, 4 * 2, 2);
		INSERT_ELEM(TF_R32G32_UINT, 4 * 2, 2);
		INSERT_ELEM(TF_R32G32_SINT, 4 * 2, 2);
		INSERT_ELEM(TF_R32G8X24_TYPELESS, 4 * 2, 2);
		INSERT_ELEM(TF_D32_FLOAT_S8X24_UINT, 4 * 2, 2);
		INSERT_ELEM(TF_R32_FLOAT_X8X24_TYPELESS, 4 * 2, 2);
		INSERT_ELEM(TF_X32_TYPELESS_G8X24_UINT, 4 * 2, 2);
		INSERT_ELEM(TF_R10G10B10A2_TYPELESS, 4, 4);
		INSERT_ELEM(TF_R10G10B10A2_UNORM, 4, 4);
		INSERT_ELEM(TF_R10G10B10A2_UINT, 4, 4);
		INSERT_ELEM(TF_R11G11B10_FLOAT, 4, 3);
		INSERT_ELEM(TF_R8G8B8A8_TYPELESS, 4, 4);
		INSERT_ELEM(TF_R8G8B8A8_UNORM, 4, 4);
		INSERT_ELEM(TF_R8G8B8A8_UNORM_SRGB, 4, 4);
		INSERT_ELEM(TF_R8G8B8A8_UINT, 4, 4);
		INSERT_ELEM(TF_R8G8B8A8_SNORM, 4, 4);
		INSERT_ELEM(TF_R8G8B8A8_SINT, 4, 4);
		INSERT_ELEM(TF_R16G16_TYPELESS, 2 * 2, 2);
		INSERT_ELEM(TF_R16G16_FLOAT, 2 * 2, 2);
		INSERT_ELEM(TF_R16G16_UNORM, 2 * 2, 2);
		INSERT_ELEM(TF_R16G16_UINT, 2 * 2, 2);
		INSERT_ELEM(TF_R16G16_SNORM, 2 * 2, 2);
		INSERT_ELEM(TF_R16G16_SINT, 2 * 2, 2);
		INSERT_ELEM(TF_R32_TYPELESS, 4, 1);
		INSERT_ELEM(TF_D32_FLOAT, 4, 1);
		INSERT_ELEM(TF_R32_FLOAT, 4, 1);
		INSERT_ELEM(TF_R32_UINT, 4, 1);
		INSERT_ELEM(TF_R32_SINT, 4, 1);
		INSERT_ELEM(TF_R24G8_TYPELESS, 4, 1);
		INSERT_ELEM(TF_D24_UNORM_S8_UINT, 4, 1);
		INSERT_ELEM(TF_R24_UNORM_X8_TYPELESS, 4, 1);
		INSERT_ELEM(TF_X24_TYPELESS_G8_UINT, 4, 1);
		INSERT_ELEM(TF_R8G8_TYPELESS, 2, 2);
		INSERT_ELEM(TF_R8G8_UNORM, 2, 2);
		INSERT_ELEM(TF_R8G8_UINT, 2, 2);
		INSERT_ELEM(TF_R8G8_SNORM, 2, 2);
		INSERT_ELEM(TF_R8G8_SINT, 2, 2);
		INSERT_ELEM(TF_R16_TYPELESS, 2, 1);
		INSERT_ELEM(TF_R16_FLOAT, 2, 1);
		INSERT_ELEM(TF_D16_UNORM, 2, 1);
		INSERT_ELEM(TF_R16_UNORM, 2, 1);
		INSERT_ELEM(TF_R16_UINT, 2, 1);
		INSERT_ELEM(TF_R16_SNORM, 2, 1);
		INSERT_ELEM(TF_R16_SINT, 2, 1);
		INSERT_ELEM(TF_R8_TYPELESS, 1, 1);
		INSERT_ELEM(TF_R8_UNORM, 1, 1);
		INSERT_ELEM(TF_R8_UINT, 1, 1);
		INSERT_ELEM(TF_R8_SNORM, 1, 1);
		INSERT_ELEM(TF_R8_SINT, 1, 1);
		INSERT_ELEM(TF_A8_UNORM, 1, 1);
		INSERT_ELEM(TF_R1_UNORM, 1, 1);
	}

	//static 
	TextureFormatHelper::FormatData TextureFormatHelper::mData;
}
