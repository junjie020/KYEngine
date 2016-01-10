#include "stdafx.h"

#include "ResourceManager.h"

#include "Common/FileSystem.h"

#include "Graphic/Resource/Shader.h"
#include "Graphic/Resource/Texture.h"


namespace KY
{
	static ShaderType from_ext_to_shader_type(const std::string &ext)
	{
		struct ExtShaderConvertPairType {
			std::string extName;
			ShaderType type;
		};

		const ExtShaderConvertPairType cvtPair[] = {
			"vs", ShdrT_Vertex,
			"ds", ShdrT_Domain,
			"hs", ShdrT_Hull,
			"gs", ShdrT_Geometry,
			"ps", ShdrT_Pixel,
		};

		std::string extTrans = ext;
		for (auto& cc : extTrans) {	cc = std::tolower(cc, std::locale());}

		for (auto pp : cvtPair) {
			if (pp.extName == ext)
				return pp.type;
		}

		return ShdrT_Count;
	}
	Shader* ResourceManager::FindAddShader(const std::string & shaderName, ShaderType type)
	{
		auto itFound = mShaders.find(shaderName);
		if (itFound != mShaders.end())
			return itFound->second;

		auto shdrPath = FileSystem::Inst()->FindFromSubPath("shader");
		auto fullshdrFileName = shdrPath / shaderName;
		std::string fileContent;
		const auto result = FileSystem::Inst()->ReadFileContent(fullshdrFileName, fileContent);
		if (result != FileSystem::ReadFileResult::RFR_Success)
			return nullptr;
		
		auto shader = new Shader;

		if (type == ShdrT_Count)
		{
			auto ext = fullshdrFileName.extension().string();
			if (!ext.empty())
			{
				ext = ext.substr(1);
				type = from_ext_to_shader_type(ext);
				if (type == ShdrT_Count)
					return nullptr;
			}
		}
		
		if (shader->InitFromCode(type, fileContent))
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

