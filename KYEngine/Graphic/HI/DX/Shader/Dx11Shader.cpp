#include "stdafx.h"
#include "Dx11Shader.h"

#include "Graphic/Graphic.h"
#include "Graphic/Resource/Shader/Shader.h"

#include "Graphic/HI/DX/Dx11.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"

#include "DebugUtils/TraceUtils.h"
#include "Common/FileSystem/FileSystem.h"

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
			case ShaderType::ShdrT_Vertex: vs(); break;
			case ShaderType::ShdrT_Hull: hs(); break;
			case ShaderType::ShdrT_Domain: ds(); break;
			case ShaderType::ShdrT_Geometry: gs(); break;
			case ShaderType::ShdrT_Pixel: ps(); break;
			default:
				BOOST_ASSERT("invaild shader type!");
				break;

			}
		}

		static inline const char* get_shader_target(FeatureLevel level, ShaderType type)
		{
			const char* targets[][uint32(ShaderType::Count)] = {
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

			return targets[uint32(level)][uint32(type)];

			
		}

		static fs::path get_valid_default_temp_file_name(const fs::path& tmpPath)
		{
			const std::string defautlName = "tempShader";
			const std::string shaderPathExt = ".hlsl";
			for (int32 idx = 0; idx < 1024; ++idx)
			{
				fs::path finalFullPath = tmpPath / (defautlName + std::to_string(idx) + shaderPathExt);
				if (fs::exists(finalFullPath))
					return finalFullPath;
			}

			
			BOOST_ASSERT("too many tmp file!!");
			return tmpPath / (defautlName + shaderPathExt);
		}

		Dx11Shader::Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry, ID3D11ClassLinkage *classLinkage, const fs::path &srcFileName /*= ""*/) 
			: mType(type)
			, mShaderCode(shaderCode)
			, mEntryName(entry)
			, mClassLinkage(classLinkage)
			, mClassInstance(0)
			, mShader(nullptr)

		{
			auto device = Graphic::Inst()->GetDx11()->GetDevice();

			ID3DBlob *pByteCode = nullptr;
			ID3DBlob *pError = nullptr;

			const auto level = Graphic::Inst()->GetDXFeatureLevel();

			const uint32 flags1 =
#ifdef _DEBUG
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION|
#endif // _DEBUG
				D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
			const uint32 flags2 = 0; // not support effect

			const D3D_SHADER_MACRO* pDefines = nullptr;
			ID3DInclude* pInclude = nullptr;
			

#ifdef _DEBUG
			// I do not know why I use D3DCompile API with file name to compile the shader, the graphic debugger do not know where to find the source file during debug.
			// so I just use the D3DCompileFromFile API, it will have the debug info when using graphic debugger.
			HRESULT hr = 0;

			fs::path tempShaderFile;
			if (!mShaderCode.empty())
			{
				fs::path tempFilePath = srcFileName.empty() ? FileSystem::Inst()->FindFromSubPath("Root") : srcFileName.parent_path();
				tempFilePath /= "TmpShaderFiles";

				if (!fs::exists(tempFilePath))
				{
					fs::create_directories(tempFilePath);
				}

				tempShaderFile = srcFileName.empty() ? get_valid_default_temp_file_name(tempFilePath) : (tempFilePath / srcFileName.filename());
				
				std::ofstream ostrm(tempShaderFile.string().c_str(), std::ios::out);
				BOOST_ASSERT(ostrm);

				ostrm.write(mShaderCode.c_str(), mShaderCode.size());
			}

			BOOST_ASSERT(fs::exists(tempShaderFile));

			if (!srcFileName.empty())
			{
				hr = D3DCompileFromFile(srcFileName.wstring().c_str(),
					pDefines, pInclude,
					entry.c_str(), get_shader_target(level, mType),
					flags1, flags2, &pByteCode, &pError);
			}
			
			if (FAILED(hr))
			{
				hr = D3DCompile(shaderCode.c_str(), shaderCode.size(),
					tempShaderFile.string().c_str(), pDefines, pInclude,
					entry.c_str(), get_shader_target(level, mType),
					flags1, flags2, &pByteCode, &pError);
			}

			if (FAILED(hr))
#else //!_DEBUG
			if (FAILED(D3DCompile(shaderCode.c_str(), shaderCode.size(),
				srcFileName, pDefines, pInclude,
				entry.c_str(), get_shader_target(level, mType),
				flags1, flags2, &pByteCode, &pError)))
#endif // _DEBUG
			{
				std::ostringstream oss;
				oss << "compile shader failed, level : " << uint32(level) << std::endl
					<< "error info : " << (const char*)pError->GetBufferPointer() << std::endl
					<< "shader code : " << shaderCode;
				DebugOutline(oss.str());
				return ;
			}

			auto beg = reinterpret_cast<const uint8*>(pByteCode->GetBufferPointer());
			auto end = beg + pByteCode->GetBufferSize();

			mShaderByteCode.assign(beg, end);

			FOR_EACH_TYPE_PERFORM(mType,
				[&](){device->CreateVertexShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mVertexShader); },
				[&](){device->CreateHullShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mHullShader); },
				[&](){device->CreateDomainShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mDomainShader); },
				[&](){device->CreateGeometryShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mGeometryShader); },
				[&](){device->CreatePixelShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), classLinkage, &mPixelShader); });


			if (nullptr == mShader)
			{
				DebugOutline("create shader failed, shader type : ", uint32(type), ", shader code : ", mShaderCode);
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
				it11->InputSlotClass = it->instanceData ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
				it11->InstanceDataStepRate = it->instanceDataStepRate;
			}

			BOOST_ASSERT(nullptr == mLayout);
			auto device = dx11->GetDevice();

			auto vs11 = vsShader.GetInternal();
			auto byteCode = vs11->GetShaderByteCode();

			BOOST_ASSERT(!byteCode.empty());
			return SUCCEEDED(device->CreateInputLayout(&*elems11.begin(), uint32(elems11.size()), &*byteCode.begin(), uint32(byteCode.size()), &mLayout));
		}

	}
}