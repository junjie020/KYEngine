#ifndef _DX11SHADER_H_
#define _DX11SHADER_H_

#include "Graphic/GraphicDef.h"

#include <d3d11.h>

namespace KY
{
	class Shader;
	namespace DX
	{
		class Dx11Shader
		{
			Dx11Shader& operator=(const Dx11Shader&);
		public:
			Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry = "main", ID3D11ClassLinkage *classLinkage = nullptr);
			~Dx11Shader();

			void Bind();
			void Unbind();

			ShaderType GetType() const { return mType;  }

			const std::string& GetCode() const { return mShaderCode;  }

			bool IsValid() const { return nullptr != mShader;  }


			//{@	internal
			template<typename D3DShaderType>
			D3DShaderType* GetInternal() const { return reinterpret_cast<D3DShaderType*>(mShader); }

			ID3D11ClassLinkage* GetClassLinkage() const { return mClassLinkage; }
			uint32 GetNumClassLinkageInstances() const { return mClassInstance; }

			const std::string& GetShaderByteCode() const { return mShaderByteCode; }
			//@}

				

		protected:


		private:
			const ShaderType  mType;
			const std::string mEntryName;
			const std::string mShaderCode;
			std::string mShaderByteCode;

			uint32 mClassInstance;
			ID3D11ClassLinkage *mClassLinkage;
			//{@
			union{
				void* mShader;
				
				//{@
				ID3D11VertexShader *mVertexShader;
				ID3D11HullShader *mHullShader;
				ID3D11DomainShader *mDomainShader;
				ID3D11GeometryShader *mGeometryShader;
				ID3D11PixelShader *mPixelShader;
				//@}
			};
			//@}

		};


		class DX11InputLayout
		{
		public:
			DX11InputLayout() : mLayout(nullptr){}
			~DX11InputLayout(){}

			void AddElement(const InputElemDesc &desc);

			bool Create(const Shader &vsShader);
			void Apply();

			bool IsValid() const { return nullptr != mLayout;  }

			ID3D11InputLayout* GetInternal() const{ return mLayout; }
		private:
			typedef std::vector<InputElemDesc>	ElemDescVec;
			ElemDescVec	mElems;
			ID3D11InputLayout *mLayout;
			
		};
	}
    
}
#endif // _DX11SHADER_H_