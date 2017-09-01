#include "stdafx.h"
#include "Material.h"

namespace KY
{

	void Material::SetRasterizerStateObj(const RasterizerState &state)
	{

	}

	void Material::SetBlendStateObj(const BlendState &state)
	{

	}

	void Material::SetDepthStencilStateObj(const BlendState &state)
	{

	}

	void Material::AddTexture(const fs::path &texPath, const SamplerState &state)
	{

	}

	void Material::AddTexture(Texture *tex, SamplerStateObj *sampler)
	{
		auto foundPos = std::find_if(mTextures.begin(), mTextures.end(), [tex](auto td) { return td.tex == tex; });
		if (foundPos == mTextures.end())
			mTextures.push_back({ tex, sampler });
	}

	void Material::SetShader(const fs::path &shaderFile)
	{

	}

}

