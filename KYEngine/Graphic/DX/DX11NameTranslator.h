#ifndef _DX11NAMETRANSLATOR_H_
#define _DX11NAMETRANSLATOR_H_

#include "Common/Singleton.h"
#include "Graphic/GraphicDef.h"
#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		class DX11NameTranslator : public Singleton<DX11NameTranslator>
		{
		public:
			D3D11_USAGE ToD3DUsage(ResourceUsage usage) const;
			DXGI_FORMAT ToDXGI_FORMAT(TexFormat ft) const;
			D3D11_BIND_FLAG ToBingFlag(BufferType type) const;
			D3D11_PRIMITIVE_TOPOLOGY ToPrimitiveTopology(PrimitiveType type) const;

		protected:


		private:

		};
	}

}
#endif // _DX11NAMETRANSLATOR_H_