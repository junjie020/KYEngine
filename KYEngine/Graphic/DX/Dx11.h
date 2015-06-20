#ifndef __DX11_H__
#define __DX11_H__

#include "../GraphicDef.h"

#include <d3d11.h>

namespace KY
{
	namespace DX
	{

		enum Dx11InitFailed
		{
			
		};

		class Dx11
		{
		public:
			Dx11();
			~Dx11();

			bool Init(const GraphicInitParam &param);
			bool BeforeRender();
			void Render();

			void Swap();

		private:

			typedef std::vector<ID3D11RenderTargetView*>	RenderTargetViewArray;
			RenderTargetViewArray	m_RenderTargetViewArray;
			ID3D11DepthStencilView	* m_pDepthStencilView;
			

			ID3D11Device		*m_pDevice;
			ID3D11DeviceContext *m_pDeviceContext;

			IDXGISwapChain		*m_pSwapChain;
		};
	}
}

#endif	//__DX11_H__