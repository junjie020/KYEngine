#include "stdafx.h"
#include "Dx11.h"
#include "Common/CommonUtils.h"

#include "Platform/Win32DefHeader.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace KY
{
	namespace DX
	{
		Dx11::Dx11()
			: m_pDevice(nullptr)
			, m_pDeviceContext(nullptr)
			, m_pSwapChain(nullptr)
			, m_pDepthStencilView(nullptr)
		{
		}

		Dx11::~Dx11()
		{
			SafeRelease(m_pDevice);
			SafeRelease(m_pDeviceContext);
			SafeRelease(m_pSwapChain);

			std::for_each(std::begin(m_RenderTargetViewArray), std::end(m_RenderTargetViewArray), [](ID3D11RenderTargetView* view){view->Release(); });
			m_RenderTargetViewArray.clear();
			SafeRelease(m_pDepthStencilView);
		}

		bool Dx11::Init(const GraphicInitParam &param)
		{
			const uint32 flags =
#ifdef _DEBUG
				D3D11_CREATE_DEVICE_DEBUG;
#else 
				0;
#endif // _DEBUG
		
			const D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
			
			D3D_FEATURE_LEVEL returnLevel = D3D_FEATURE_LEVEL_11_0;
			if (FAILED(::D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
				levels, _countof(levels), D3D11_SDK_VERSION, &m_pDevice, &returnLevel, &m_pDeviceContext)))
				return false;

			IDXGIFactory *dxgi = nullptr;
			if (FAILED(::CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&dxgi))))
				return false;
			
			DXGI_SWAP_CHAIN_DESC swapDesc = { 0 };

			swapDesc.BufferDesc.Width		= param.width;
			swapDesc.BufferDesc.Height		= param.height;
			swapDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;		
			swapDesc.Windowed				= TRUE;
			
			swapDesc.SampleDesc.Count		= std::max(uint32(1), param.sampleDesc.count);
			m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, swapDesc.SampleDesc.Count, &swapDesc.SampleDesc.Quality);
			swapDesc.SampleDesc.Quality		= std::min(swapDesc.SampleDesc.Quality, param.sampleDesc.level);

	
			swapDesc.BufferCount = 1;
			swapDesc.OutputWindow = param.hwnd;
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

			if (FAILED(dxgi->CreateSwapChain(m_pDevice, &swapDesc, &m_pSwapChain)))
				return false;

			ID3D11Texture2D *pSwapBuffer = nullptr;
			BOOST_VERIFY(SUCCEEDED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&pSwapBuffer))));

			ID3D11RenderTargetView *pRTView = nullptr;
			if (FAILED(m_pDevice->CreateRenderTargetView(pSwapBuffer, 0, &pRTView)))
				return false;

			m_RenderTargetViewArray.push_back(pRTView);

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
			if (FAILED(m_pDevice->CreateTexture2D(&depthTexDesc, 0, &pDepthBuffer)))
				return false;

			if (FAILED(m_pDevice->CreateDepthStencilView(pDepthBuffer, nullptr, &m_pDepthStencilView)))
				return false;

			SafeRelease(dxgi);
			return true;
		}

		void Dx11::Swap()
		{
			m_pSwapChain->Present(0, 0);
		}

		bool Dx11::BeforeRender()
		{
			m_pDeviceContext->OMSetRenderTargets(m_RenderTargetViewArray.size(), &*m_RenderTargetViewArray.begin(), m_pDepthStencilView);

			float colors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			m_pDeviceContext->ClearRenderTargetView(m_RenderTargetViewArray[0], colors);
			return true;
		}

		void Dx11::Render()
		{

		}

	}



}