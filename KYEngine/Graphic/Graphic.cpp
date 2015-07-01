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
		: mDx(nullptr)
	{
	}


	Graphic::~Graphic()
	{
		SafeDelete(mDx);
	}


	bool Graphic::Initialize(const GraphicInitParam &param)
	{
		SafeDelete(mDx);
		mDx = new DX::Dx11;

		return mDx->Init(param);
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
		if (mDx->BeforeRender())
		{
			mDx->Swap();
			mDx->Render();
		}
			

		return true;
	}
}