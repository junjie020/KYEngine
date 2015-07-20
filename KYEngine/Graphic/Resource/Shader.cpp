#include "stdafx.h"
#include "Shader.h"

#include "Graphic/GraphicDef.h"
#include "Graphic/DX/Buffer/Dx11Shader.h"

namespace KY
{
	Shader::Shader()	
		: mShaderImpl(nullptr)
	{

	}

	Shader::~Shader()
	{
		SafeDelete(mShaderImpl);
	}

	bool Shader::InitFromFile(ShaderType type, const fs::path &file, const std::string &entry)
	{
		std::ifstream iftm(file.string().c_str());

		if (iftm)
		{
			iftm.seekg(std::ios::end);
			const std::streamoff sizeInBytes = iftm.tellg();
			iftm.seekg(std::ios::beg);

			if (sizeInBytes != 0)
			{
				std::string code;
				code.resize(size_t(sizeInBytes));
				iftm.read(&*code.begin(), sizeInBytes);

				return InitFromCode(type, code, entry);
			}
		}

		return false;
	}

	bool Shader::InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry)
	{
		SafeDelete(mShaderImpl);
		mShaderImpl = new DX::Dx11Shader(type, shaderCode, entry);		
		return mShaderImpl != nullptr;
	}

	KY::ShaderType Shader::GetType() const
	{
		return mShaderImpl->GetType();
	}

}