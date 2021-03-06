#include "stdafx.h"
#include "Dx11.h"
#include "Common/CommonUtils.h"

#include "Platform/Win32DefHeader.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace KY
{
	namespace DX
	{
		Dx11::Dx11()
			: mDevice(nullptr)
			, mDeviceContext(nullptr)
#ifdef _DEBUG
			, mDebug(nullptr)
#endif // _DEBUG			
			, mSwapChain(nullptr)
			, mDepthStencilView(nullptr)
			, mFeatureLevel(FeatureLevel::FL_Unknown)
		{
			DX11NameTranslator::Create();
		}

		Dx11::~Dx11()
		{
			DX11NameTranslator::Destroy();

			SafeRelease(mDevice);
			SafeRelease(mDeviceContext);
			SafeRelease(mSwapChain);

			std::for_each(std::begin(mRenderTargetViewArray), std::end(mRenderTargetViewArray), [](ID3D11RenderTargetView* view){view->Release(); });
			mRenderTargetViewArray.clear();
			SafeRelease(mDepthStencilView);
		}

		bool Dx11::Init(const GraphicInitParam &param)
		{
			const uint32 flags =
#ifdef _DEBUG
				D3D11_CREATE_DEVICE_DEBUG;
#else 
				0;
#endif // _DEBUG
		
			D3D_FEATURE_LEVEL returnLevel = D3D_FEATURE_LEVEL_11_1;

			auto wantedLevel = param.featureLevel;

			std::vector<D3D_FEATURE_LEVEL>	levels;
			
			if (wantedLevel == FeatureLevel::FL_Unknown)
			{
				std::vector<D3D_FEATURE_LEVEL> tmplevels = {
					D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
					D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2,
					D3D_FEATURE_LEVEL_9_1,
				};

				levels.swap(tmplevels);
			}
			else
			{
				for (int32 ii = int32(wantedLevel); ii  >= 0; --ii)
					levels.push_back(DX11NameTranslator::Inst()->ToFeatureLevel(FeatureLevel(ii)));
			
			}
			
			if (FAILED(::D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
				&*levels.begin(), uint32(levels.size()), D3D11_SDK_VERSION, &mDevice, &returnLevel, &mDeviceContext)))
				return false;

			mFeatureLevel = DX11NameTranslator::Inst()->FromeFeatureLevel(returnLevel);
			BOOST_ASSERT(mFeatureLevel != FeatureLevel::FL_Unknown);

			IDXGIFactory *dxgi = nullptr;
			if (FAILED(::CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&dxgi))))
				return false;

#ifdef _DEBUG
			if (FAILED(mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void **>(&mDebug))))
				return false;
#endif //_DEBUG
			
			DXGI_SWAP_CHAIN_DESC swapDesc = { 0 };
			
			swapDesc.BufferDesc.Width		= param.width;
			swapDesc.BufferDesc.Height		= param.height;
			swapDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;		
			swapDesc.Windowed				= TRUE;
			
			swapDesc.SampleDesc.Count		= std::max(uint32(1), param.sampleDesc.count);
			mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, swapDesc.SampleDesc.Count, &swapDesc.SampleDesc.Quality);
			swapDesc.SampleDesc.Quality		= std::min(swapDesc.SampleDesc.Quality, param.sampleDesc.level);

	
			swapDesc.BufferCount = 1;
			swapDesc.OutputWindow = param.hwnd;
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

			if (FAILED(dxgi->CreateSwapChain(mDevice, &swapDesc, &mSwapChain)))
				return false;

			ID3D11Texture2D *pSwapBuffer = nullptr;
			BOOST_VERIFY(SUCCEEDED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&pSwapBuffer))));

			ID3D11RenderTargetView *pRTView = nullptr;
			if (FAILED(mDevice->CreateRenderTargetView(pSwapBuffer, 0, &pRTView)))
				return false;

			mRenderTargetViewArray.push_back(pRTView);

			D3D11_TEXTURE2D_DESC depthTexDesc;
			depthTexDesc.Width = param.width;
			depthTexDesc.Height = param.height;
			depthTexDesc.MipLevels = 1;
			depthTexDesc.ArraySize = 1;
			depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthTexDesc.SampleDesc = swapDesc.SampleDesc;

			depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
			depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthTexDesc.CPUAccessFlags = 0;
			depthTexDesc.MiscFlags = 0;

			ID3D11Texture2D *pDepthBuffer = nullptr;
			if (FAILED(mDevice->CreateTexture2D(&depthTexDesc, 0, &pDepthBuffer)))
				return false;

			if (FAILED(mDevice->CreateDepthStencilView(pDepthBuffer, nullptr, &mDepthStencilView)))
				return false;

			SafeRelease(dxgi);				
			return true;
		}

		void Dx11::Swap()
		{
			mSwapChain->Present(0, 0);
		}

		bool Dx11::Prepare()
		{
			
			mDeviceContext->OMSetRenderTargets(1, &mRenderTargetViewArray[0], mDepthStencilView);

			float colors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			mDeviceContext->ClearRenderTargetView(mRenderTargetViewArray[0], colors);

			mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			
			return true;
		}
	}



}