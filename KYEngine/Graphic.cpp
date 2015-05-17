////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Graphic.h"
#include "Dx11.h"

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


	bool Graphic::Initialize(int screenWidth, int screenHeight, HWND hwnd)
	{
		m_pDx = new DX::Dx11;



		return true;
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