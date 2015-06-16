////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Graphic.h"
#include "DX/Dx11.h"

namespace KY
{
	Graphic::Graphic()
		: m_pDx(NULL)
	{
	}


	Graphic::Graphic(const Graphic& other)
	{
	}


	Graphic::~Graphic()
	{
	}


	bool Graphic::Initialize(const GraphicInitParam &param)
	{

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

		return true;
	}
}