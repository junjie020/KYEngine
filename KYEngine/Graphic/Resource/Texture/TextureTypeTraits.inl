#pragma once

#include "Graphic/Resource/Texture/TextureTypeTraits.h"

namespace KY
{
	template<TextureType TType, class HITextureType>
	void TextureTypeTraits<TType, HITextureType>::Destory()
	{
		SafeDelete(mTex);
	}

	template<TextureType TType, class HITextureType>
	HITextureType* TextureTypeTraits<TType, HITextureType>::Create()
	{
		BOOST_ASSERT(nullptr == mTex);
		mTex = new HITextureType;

		return mTex;
	}
}