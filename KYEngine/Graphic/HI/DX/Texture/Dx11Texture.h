#pragma once
#ifndef _DX11TEXTURE_H_
#define _DX11TEXTURE_H_

#include "Graphic/GraphicDef.h"

#include <d3d11.h>
namespace KY
{
	using RawBuffer = std::vector<uint8>;

	class Dx11Texture1D
	{
	public:

	};

    class Dx11Texture2D
    {
    public:		
		Dx11Texture2D() : mTexture(nullptr) {}

		~Dx11Texture2D() {
			SafeRelease(mTexture);			
		}

		bool Create(const Texture2DParam &param, const ResourceData &resData);
		bool Create(const TextureParam &param, class TextureAssertLoader *loader);

		bool IsValid() const {
			return nullptr != mTexture;
		}

		ID3D11Texture2D* GetInternal() const { return mTexture; }

	private:
		ID3D11Texture2D* mTexture;

    };

	class Dx11Texture3D
	{
	public:

	};

	class Dx11TextureCube
	{
	public:

	};
}
#endif // _DX11TEXTURE_H_
