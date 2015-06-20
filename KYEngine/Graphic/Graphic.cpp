////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Graphic.h"
#include "DX/Dx11.h"
#include "Common/CommonUtils.h"
namespace KY
{
	Graphic::Graphic()
		: m_pDx(nullptr)
	{
	}


	Graphic::~Graphic()
	{
		SafeDelete(m_pDx);
	}


	bool Graphic::Initialize(const GraphicInitParam &param)
	{
		SafeDelete(m_pDx);
		m_pDx = new DX::Dx11;

		return m_pDx->Init(param);
	}


	void Graphic::Shutdown()
	{

		return;
	}


	bool Graphic::Frame()
	{
		Render();
		return true;
	}


	bool Graphic::Render()
	{
		if (m_pDx->BeforeRender())
		{
			m_pDx->Swap();
			m_pDx->Render();
		}
			

		return true;
	}
}