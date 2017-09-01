#pragma once

#include "Common/Singleton.h"
#include "Graphic/GraphicDef.h"

namespace KY
{
	class Shader;
	class Texture;

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		Shader* FindAddShader(const std::string &shaderName, ShaderType type = ShaderType::Count);
		Texture* FindAddTexture(const std::string &texName);
	private:
		using ShaderRes = std::unordered_map<std::string, Shader*>;
		ShaderRes	mShaders;
		using TextureRes = std::unordered_map<std::string, Texture*>;
		TextureRes	mTextures;
	};
}


