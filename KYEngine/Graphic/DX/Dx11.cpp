#include "stdafx.h"
#include "Dx11.h"
#include "Common/CommonUtils.h"

#include "Win32DefHeader.h"

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
		{
		}

		Dx11::~Dx11()
		{
			SafeRelease(m_pDevice);
			SafeRelease(m_pDeviceContext);
			SafeRelease(m_pSwapChain);
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
			swapDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
			swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapDesc.BufferDesc.Scaling		= DXGI_MODE_SCALING_UNSPECIFIED;

			swapDesc.SampleDesc.Count		= std::max(uint32(1), param.sampleDesc.count);
			m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, swapDesc.SampleDesc.Count, &swapDesc.SampleDesc.Quality);
			swapDesc.SampleDesc.Quality		= std::max(swapDesc.SampleDesc.Quality, param.sampleDesc.level);

	
			swapDesc.BufferCount = 2;
			swapDesc.OutputWindow = param.hwnd;
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			if (FAILED(dxgi->CreateSwapChain(m_pDevice, &swapDesc, &m_pSwapChain)))
				return false;

			return true;
		}
	}



}