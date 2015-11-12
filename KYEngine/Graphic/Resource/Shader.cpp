#include "stdafx.h"
#include "Shader.h"

#include "Graphic/GraphicDef.h"
#include "Graphic/DX/Buffer/Dx11Shader.h"
#include <fstream>

namespace KY
{
	Shader::Shader()	
		: Resource(ResT_Shader)
		, mShaderImpl(nullptr)
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

	bool Shader::InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry)
	{
		SafeDelete(mShaderImpl);
		mShaderImpl = new DX::Dx11Shader(type, shaderCode, entry);		
		return mShaderImpl != nullptr;
	}

	KY::ShaderType Shader::GetShaderType() const
	{
		return mShaderImpl->GetType();
	}

	bool Shader::IsValid() const
	{
		return mShaderImpl && mShaderImpl->IsValid();
	}

	//////////////////////////////////////////////////////////////////////////

	InputLayout::InputLayout()
		:mLayout(nullptr)
	{

	}

	InputLayout::~InputLayout()
	{
		SafeDelete(mLayout);
	}

	void InputLayout::AddElem(const InputElemDesc &elem)
	{
		if (nullptr == mLayout)
			mLayout = new DX::DX11InputLayout;

		mLayout->AddElement(elem);
	}

	bool InputLayout::Create(const Shader &vs)
	{
		BOOST_ASSERT(mLayout);

		return mLayout->Create(vs);
	}

	bool InputLayout::IsValid() const
	{
		return mLayout && mLayout->IsValid();
	}

	void InputLayout::Clean()
	{
		SafeDelete(mLayout);
	}

}