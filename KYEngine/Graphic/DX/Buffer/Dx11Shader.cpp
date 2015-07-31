#include "stdafx.h"
#include "Dx11Shader.h"

#include "Graphic/Graphic.h"
#include "Graphic/Resource/Shader.h"

#include "Graphic/DX/Dx11.h"
#include "Graphic/DX/DX11NameTranslator.h"

#include "DebugUtils/TraceUtils.h"

#include <functional>

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

		Dx11Shader::Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry /*= "main"*/, ID3D11ClassLinkage *classLinkage /*= nullptr*/)
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
			auto code = vs11->GetCode();

			BOOST_ASSERT(!code.empty());

			return SUCCEEDED(device->CreateInputLayout(&*elems11.begin(), elems11.size(), &*code.begin(), code.size(), &mLayout));
		}

	}
}