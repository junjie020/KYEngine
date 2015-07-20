#ifndef _DX11SHADER_H_
#define _DX11SHADER_H_

#include "Graphic/GraphicDef.h"

#include <d3d11.h>

namespace KY
{
	namespace DX
	{
		class Dx11Shader
		{
		public:
			Dx11Shader(ShaderType type, const std::string &shaderCode, const std::string &entry = "main", ID3D11ClassLinkage *classLinkage = nullptr);
			~Dx11Shader();

			void Bind();
			void Unbind();

			ShaderType GetType() const { return mType;  }

		protected:


		private:
			const ShaderType  mType;
			const std::string mEntryName;
			const std::string mShaderCode;
			ID3D11ClassLinkage *mClassLinkage;
			//{@
			union{
				void* mShader;
				struct {
					ID3D11VertexShader *mVertexShader;
					ID3D11HullShader *mHullShader;
					ID3D11DomainShader *mDomainShader;
					ID3D11GeometryShader *mGeometryShader;
					ID3D11PixelShader *mPixelShader;
				};
			};
			//@}

		};
	}
    
}
#endif // _DX11SHADER_H_