#include "stdafx.h"

#include "ResourceManager.h"

#include "Common/FileSystem/FileSystem.h"

#include "Graphic/Resource/Shader/Shader.h"
#include "Graphic/Resource/Texture/Texture.h"
#include "Graphic/Resource/Shader/Compile/ShaderCodeRegenerate.h"


namespace KY
{
	static ShaderType from_ext_to_shader_type(const std::string &ext)
	{
		struct ExtShaderConvertPairType {
			std::string extName;
			ShaderType type;
		};

		const ExtShaderConvertPairType cvtPair[] = {
			"vs", ShaderType::ShdrT_Vertex,
			"ds", ShaderType::ShdrT_Domain,
			"hs", ShaderType::ShdrT_Hull,
			"gs", ShaderType::ShdrT_Geometry,
			"ps", ShaderType::ShdrT_Pixel,
		};

		std::string extTrans = ext;
		for (auto& cc : extTrans) {	cc = std::tolower(cc, std::locale());}

		for (auto pp : cvtPair) {
			if (pp.extName == ext)
				return pp.type;
		}

		return ShaderType::Count;
	}
	Shader* ResourceManager::FindAddShader(const std::string & shaderName, ShaderType type)
	{
		auto itFound = mShaders.find(shaderName);
		if (itFound != mShaders.end())
			return itFound->second;

		auto shdrPath = FileSystem::Inst()->FindFromSubPath("shader");
		auto fullshdrFileName = shdrPath / shaderName;

		ShaderCodeRegenerate code;
		std::string fileContent = code.Regenerate(fullshdrFileName);
		
		if (fileContent.empty())
			return nullptr;
		
		auto shader = new Shader;

		if (type == ShaderType::Count)
		{
			auto ext = fullshdrFileName.extension().string();
			if (!ext.empty())
			{
				ext = ext.substr(1);
				type = from_ext_to_shader_type(ext);
				if (type == ShaderType::Count)
					return nullptr;
			}
		}
		
		if (shader->InitFromCode(type, fileContent, "main", fullshdrFileName.string()))
		{
			mShaders.insert(std::make_pair(shaderName, shader));
			return shader;
		}
			
		return nullptr;
	}

	Texture* ResourceManager::FindAddTexture(const std::string & texName)
	{
		auto itFound = mTextures.find(texName);
		if (itFound != mTextures.end())
			return itFound->second;

		BOOST_ASSERT(false && "not impl");
		return nullptr;
	}
}

