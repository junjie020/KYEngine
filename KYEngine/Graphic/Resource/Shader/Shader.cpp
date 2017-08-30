#include "stdafx.h"
#include "Shader.h"

#include "Graphic/GraphicDef.h"
#include "Graphic/HI/DX/Shader/Dx11Shader.h"
#include <fstream>

namespace KY
{
	Shader::Shader()	
		: Resource(ResourceType::Shader)		
	{

	}

	bool Shader::InitFromFile(ShaderType type, const fs::path &file, const std::string &entry)
	{
		std::ifstream iftm(file.string().c_str());

		if (iftm)
		{
			iftm.seekg(0, std::ios::end);
			const std::streamoff sizeInBytes = iftm.tellg();
			iftm.seekg(0, std::ios::beg);

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

	bool Shader::InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry /*= "main"*/, const std::string &srcFileName /*= ""*/)
	{
		SafeDelete(mDx11Internal);
		mDx11Internal = new DX::Dx11Shader(type, shaderCode, entry, nullptr, srcFileName);
		return mDx11Internal != nullptr;
	}

	KY::ShaderType Shader::GetShaderType() const
	{
		return mDx11Internal->GetType();
	}

	//////////////////////////////////////////////////////////////////////////	
	void InputLayout::AddElem(const InputElemDesc &elem)
	{
		if (nullptr == mDx11Internal)
			mDx11Internal = new DX::DX11InputLayout;

		mDx11Internal->AddElement(elem);
	}

	bool InputLayout::Init(const Shader &vs)
	{
		BOOST_ASSERT(mDx11Internal);

		return mDx11Internal->Create(vs);
	}

	void InputLayout::Clean()
	{
		SafeDelete(mDx11Internal);
	}

}