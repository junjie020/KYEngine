#ifndef __DX11_H__
#define __DX11_H__

#include "../GraphicDef.h"

#include <d3d11.h>

namespace KY
{
	namespace DX
	{
		class Dx11
		{
		public:
			Dx11();
			~Dx11();
			bool Init(const GraphicInitParam &param);

		private:
			ID3D11Device		*m_pDevice;
			ID3D11DeviceContext *m_pDeviceContext;

			IDXGISwapChain		*m_pSwapChain;
		};
	}
}

#endif	//__DX11_H__