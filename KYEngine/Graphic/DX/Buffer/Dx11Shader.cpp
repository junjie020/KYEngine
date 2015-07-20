#include "stdafx.h"
#include "Dx11Shader.h"

#include "Graphic/Graphic.h"
#include "Graphic/DX/Dx11.h"

#include "DebugUtils/TraceUtils.h"

#include <functional>

namespace KY
{
	template<class VSOp, class HSOp, class DSOp, class GSOp, class PSOp>
	static inline void FOR_EACH_TYPE_PERFORM(ShaderType type, VSOp vs, HSOp hs, DSOp ds, GSOp gs, PSOp ps)
	{
		switch (type){
		case ST_Vertex: vs(); break;
		case ST_Hull: hs(); break;
		case ST_Domain: ds(); break;
		case ST_Geometry: gs(); break;
		case ST_Pixel: ps(); break;
		default:
			BOOST_ASSERT("invaild shader type!");
			break;

		}
	}
	
	DX::Dx11Shader::Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry /*= "main"*/, ID3D11ClassLinkage *classLinkage /*= nullptr*/)
		: mType(type)
		, mShaderCode(shaderCode)
		, mEntryName(entry)
		, mClassLinkage(classLinkage)
		, mShader(nullptr)
	{
		auto device = Graphic::Inst()->GetDx11()->GetDevice();
		bool success = false;

		FOR_EACH_TYPE_PERFORM(mType,
			[&](){device->CreateVertexShader(mShaderCode.c_str(), mShaderCode.length(), classLinkage, &mVertexShader); },
			[&](){device->CreateHullShader(mShaderCode.c_str(), mShaderCode.length(), classLinkage, &mHullShader); },
			[&](){device->CreateDomainShader(mShaderCode.c_str(), mShaderCode.length(), classLinkage, &mDomainShader); },
			[&](){device->CreateGeometryShader(mShaderCode.c_str(), mShaderCode.length(), classLinkage, &mGeometryShader); },
			[&](){device->CreatePixelShader(mShaderCode.c_str(), mShaderCode.length(), classLinkage, &mPixelShader); });


		if (nullptr == mShader)
		{
			std::ostringstream oss;
			oss << "create shader failed, shader type : " << mType << std::endl
				<< ", shader code : " << mShaderCode << std::endl;

			DebugOutline(oss.str());
		}
	}

	DX::Dx11Shader::~Dx11Shader()
	{
		if (mShader)
		{
			FOR_EACH_TYPE_PERFORM(mType,
				[&](){SafeRelease(mVertexShader); },
				[&](){SafeRelease(mHullShader); },
				[&](){SafeRelease(mDomainShader); },
				[&](){SafeRelease(mGeometryShader); },
				[&](){SafeRelease(mPixelShader); });
		}
	}

	void DX::Dx11Shader::Bind()
	{
		BOOST_ASSERT(mShader);

		auto context = Graphic::Inst()->GetDx11()->GetDeviceContext();

		FOR_EACH_TYPE_PERFORM(mType,
			[&](){context->VSSetShader(mVertexShader, 0, 0); },
			[&](){context->HSSetShader(mHullShader, 0, 0); },
			[&](){context->DSSetShader(mDomainShader, 0, 0); },
			[&](){context->GSSetShader(mGeometryShader, 0, 0); },
			[&](){context->PSSetShader(mPixelShader, 0, 0); });
	}

	void DX::Dx11Shader::Unbind()
	{
		auto context = Graphic::Inst()->GetDx11()->GetDeviceContext();
		FOR_EACH_TYPE_PERFORM(mType,
			[&](){context->VSSetShader(nullptr, 0, 0); },
			[&](){context->HSSetShader(nullptr, 0, 0); },
			[&](){context->DSSetShader(nullptr, 0, 0); },
			[&](){context->GSSetShader(nullptr, 0, 0); },
			[&](){context->PSSetShader(nullptr, 0, 0); });
	}

}