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

			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetDeviceContext();

		private:

			typedef std::vector<ID3D11RenderTargetView*>	RenderTargetViewArray;
			RenderTargetViewArray	mRenderTargetViewArray;
			ID3D11DepthStencilView	* mDepthStencilView;
			
			ID3D11Debug			*mDebug;
			ID3D11Device		*mDevice;
			ID3D11DeviceContext *mDeviceContext;

			IDXGISwapChain		*mSwapChain;
		};

		inline ID3D11Device* Dx11::GetDevice(){
			return mDevice;
		}

		inline ID3D11DeviceContext* Dx11::GetDeviceContext(){
			return mDeviceContext;
		}
	}
}

#endif	//__DX11_H__