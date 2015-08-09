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
			bool Prepare();			

			void Swap();

			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetDeviceContext();
			FeatureLevel GetSelectedFeatureLevel() const;

		private:

			typedef std::vector<ID3D11RenderTargetView*>	RenderTargetViewArray;
			RenderTargetViewArray	mRenderTargetViewArray;
			ID3D11DepthStencilView	* mDepthStencilView;
#ifdef _DEBUG
			ID3D11Debug			*mDebug;
#endif // _DEBUG
			
			ID3D11Device		*mDevice;
			ID3D11DeviceContext *mDeviceContext;

			IDXGISwapChain		*mSwapChain;
			FeatureLevel		mFeatureLevel;
		};

		inline ID3D11Device* Dx11::GetDevice(){
			return mDevice;
		}

		inline ID3D11DeviceContext* Dx11::GetDeviceContext(){
			return mDeviceContext;
		}

		inline FeatureLevel Dx11::GetSelectedFeatureLevel() const{
			return mFeatureLevel;
		}
			
	}
}

#endif	//__DX11_H__