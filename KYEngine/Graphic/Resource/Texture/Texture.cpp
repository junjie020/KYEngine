#include "stdafx.h"
#include "Texture.h"
#include "Texture.inl"
#include "Graphic/HI/DX/Texture/Dx11Texture.h"

#include "Graphic/Resource/Texture/TextureTypeTraits.inl"

namespace KY
{
	using Texture2D = TextureImpl<TextureTypeTraits<TextureType::TT_2D, Dx11Texture2D>>;


	void text()
	{
		auto cc = new Texture2D();

		cc->Init(TextureParam(), nullptr);
	}
}
