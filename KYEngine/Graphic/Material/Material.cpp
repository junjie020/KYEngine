#include "stdafx.h"
#include "Material.h"

namespace KY
{

	void Material::Update()
	{

	}

	void Material::SetRasterizerStateObj(const RasterizerState &state)
	{

	}

	void Material::SetBlendStateObj(const BlendState &state)
	{

	}

	void Material::SetDepthStencilStateObj(const BlendState &state)
	{

	}

	void Material::AddTexture(const fs::path &texPath, const SamplerState &state, const std::string &texName /*= ""*/)
	{

	}

	void Material::AddTexture(const Texture *tex, SamplerStateObj *sampler, const std::string &texName)
	{

	}

	void Material::SetTexture(const Texture *tex, const std::string &texName)
	{

	}

	void Material::SetSamplerState(const SamplerState &state, const std::string &texName)
	{

	}

	void Material::SetShader(const fs::path &shaderFile, ShaderType type)
	{

	}
}

