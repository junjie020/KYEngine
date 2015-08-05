#include "stdafx.h"
#include "Dx11Shader.h"

#include "Graphic/Graphic.h"
#include "Graphic/Resource/Shader.h"

#include "Graphic/DX/Dx11.h"
#include "Graphic/DX/DX11NameTranslator.h"

#include "DebugUtils/TraceUtils.h"

#include <functional>

//{@	we need replace it by LoadLibrary("D3DCompiler_43.dll"), and get the function process which name is "D3DCompile"
#include <D3Dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")
//@}



namespace KY
{
	namespace DX
	{


		template<class VSOp, class HSOp, class DSOp, class GSOp, class PSOp>
		static inline void FOR_EACH_TYPE_PERFORM(ShaderType type, VSOp vs, HSOp hs, DSOp ds, GSOp gs, PSOp ps)
		{
			switch (type){
			case ShdrT_Vertex: vs(); break;
			case ShdrT_Hull: hs(); break;
			case ShdrT_Domain: ds(); break;
			case ShdrT_Geometry: gs(); break;
			case ShdrT_Pixel: ps(); break;
			default:
				BOOST_ASSERT("invaild shader type!");
				break;

			}
		}

		static inline const char* get_shader_target(FeatureLevel level, ShaderType type)
		{
			const char* targets[][ShdrT_Count] = {
				"",		  "",		"",		  "",		"ps_1_0",
				"vs_2_0", "",		"",		  "",		"ps_2_0",
				"vs_3_0", "",		"",		  "",		"ps_3_0",
				"vs_4_0", "",		"",		  "gs_4_0", "ps_4_0",
				"vs_4_1", "",		"",		  "gs_4_1", "ps_4_1",
				"vs_5_0", "hs_5_0", "ds_5_0", "gs_5_0", "ps_5_0",
				"vs_5_0", "hs_5_0", "ds_5_0", "gs_5_0", "ps_5_0",
			};

			BOOST_ASSERT(COUNT_OF(targets) > uint32(level));
			BOOST_ASSERT(COUNT_OF(targets[0]) > uint32(type));

			return targets[level][type];

			
		}

		Dx11Shader::Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry /*= "main"*/, ID3D11ClassLinkage *classLinkage /*= nullptr*/)
			: mType(type)
			, mShaderCode(shaderCode)
			, mEntryName(entry)
			, mClassLinkage(classLinkage)
			, mClassInstance(0)
			, mShader(nullptr)

		{
			auto device = Graphic::Inst()->GetDx11()->GetDevice();
			bool success = false;


			ID3DBlob *pByteCode = nullptr;
			ID3DBlob *pError = nullptr;

			const auto level = Graphic::Inst()->GetDXFeatureLevel();

			const uint32 flags1 =
#ifdef _DEBUG
				D3DCOMPILE_DEBUG |
#endif // _DEBUG
				D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
			const uint32 flags2 = 0; // not support effect

			const char* srcFileName = "";
			const D3D_SHADER_MACRO* pDefines = nullptr;
			ID3DInclude* pInclude = nullptr;
			
			if (FAILED(D3DCompile(shaderCode.c_str(), shaderCode.size(),
				srcFileName, pDefines, pInclude,
				entry.c_str(), get_shader_target(level, mType),
				flags1, flags2, &pByteCode, &pError)))
			{
				std::ostringstream oss;
				oss << "compile shader failed, level : " << level << std::endl
					<< ", error info : " << (const char*)pError->GetBufferPointer() << std::endl
					<< ", shader code : " << shaderCode;
				DebugOutline(oss.str());
				return ;
			}

			mShaderByteCode.assign((const char*)pByteCode->GetBufferPointer(), pByteCode->GetBufferSize());


			FOR_EACH_TYPE_PERFORM(mType,
				[&](){device->CreateVertexShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mVertexShader); },
				[&](){device->CreateHullShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mHullShader); },
				[&](){device->CreateDomainShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mDomainShader); },
				[&](){device->CreateGeometryShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mGeometryShader); },
				[&](){device->CreatePixelShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mPixelShader); });


			if (nullptr == mShader)
			{
				std::ostringstream oss;
				oss << "create shader failed, shader type : " << mType << std::endl
					<< ", shader code : " << mShaderCode << std::endl;

				DebugOutline(oss.str());
			}
		}

		Dx11Shader::~Dx11Shader()
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

		void Dx11Shader::Bind()
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

		void Dx11Shader::Unbind()
		{
			auto context = Graphic::Inst()->GetDx11()->GetDeviceContext();
			FOR_EACH_TYPE_PERFORM(mType,
				[&](){context->VSSetShader(nullptr, 0, 0); },
				[&](){context->HSSetShader(nullptr, 0, 0); },
				[&](){context->DSSetShader(nullptr, 0, 0); },
				[&](){context->GSSetShader(nullptr, 0, 0); },
				[&](){context->PSSetShader(nullptr, 0, 0); });
		}
		//////////////////////////////////////////////////////////////////////////
		void DX11InputLayout::AddElement(const InputElemDesc &desc)
		{
			mElems.push_back(desc);
		}

		void DX11InputLayout::Apply()
		{
			BOOST_ASSERT(mLayout);
			auto dx11 = Graphic::Inst()->GetDx11();
		
			
			auto context = dx11->GetDeviceContext();
			context->IASetInputLayout(mLayout);
		}

		bool DX11InputLayout::Create(const Shader &vsShader)
		{
			auto dx11 = Graphic::Inst()->GetDx11();
			const D3D11_INPUT_ELEMENT_DESC zeroDesc = { 0 };
			std::vector<D3D11_INPUT_ELEMENT_DESC>	elems11(mElems.size(), zeroDesc);

			auto it11 = elems11.begin();
			for (auto it = mElems.begin(); it != mElems.end(); ++it, ++it11)
			{
				it11->SemanticName = it->semanticName;
				it11->SemanticIndex = it->semanticIndex;
				it11->Format = DX11NameTranslator::Inst()->ToDXGI_FORMAT(it->format);
				it11->InputSlot = it->inputSlot;
				it11->AlignedByteOffset = it->alignedByteOffset;
			}

			BOOST_ASSERT(nullptr == mLayout);
			auto device = dx11->GetDevice();

			auto vs11 = vsShader.GetInternal();
			auto byteCode = vs11->GetShaderByteCode();

			BOOST_ASSERT(!byteCode.empty());
			return SUCCEEDED(device->CreateInputLayout(&*elems11.begin(), elems11.size(), &*byteCode.begin(), byteCode.size(), &mLayout));
		}

	}
}