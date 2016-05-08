#pragma once
#ifndef _DX11TEXTURE_H_
#define _DX11TEXTURE_H_

#include "Graphic/GraphicDef.h"

#include "Graphic/HI/DX/Dx11HardwareInterface.h"
#include "Graphic/HI/DX/Dx11Resource.h"

#include <d3d11.h>
namespace KY
{
	class TextureAssertLoader;

	namespace DX
	{
		using RawBuffer = std::vector<uint8>;

		class Dx11Texture1D : public Dx11HardwareInterface<ID3D11Texture1D>
							//, public Dx11Resource
		{
		public:

		};

		class Dx11Texture2D : public Dx11HardwareInterface<ID3D11Texture2D>
							//, public Dx11Resource
		{
		public:
			bool Create(const Texture2DParam &param, const ResourceData &resData);
			bool Create(const TextureParam &param, TextureAssertLoader *loader);

			//virtual ID3D11Resource * GetDxResource() override
			//{
			//	return GetInternal();
			//}
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

}
#endif // _DX11TEXTURE_H_
