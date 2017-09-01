#pragma once

#include "Graphic/HI/DX/Texture/Dx11Texture.h"
#include "Graphic/Resource/Texture/Texture.h"
#include "Graphic/Resource/Texture/TextureTypeTraits.h"

namespace KY
{
	template<class TraitsType>
	TextureImpl<TraitsType>::~TextureImpl()
	{
		Destory();
	}

	template<class TraitsType>
	bool TextureImpl<TraitsType>::Init(const TextureParam &param, TextureAssertLoader *loader)
	{
		auto hiTex = mTex.Create();
		BOOST_ASSERT(hiTex);

		return hiTex->Create(param, loader);
	}

	template<class TraitsType>
	void TextureImpl<TraitsType>::Destory()
	{
		mTex.Destory();
	}
}