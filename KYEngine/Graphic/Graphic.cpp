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

	void Graphic::AddRenderOperation(RenderOperation *ro)
	{
		BOOST_ASSERT(mQueue);
		mQueue->Push(ro);
	}

	bool Graphic::Render()
	{
		if (mDx->Prepare())
		{
			mDx->Swap();
			CommitRenderData();			
		}

		return true;
	}

	void Graphic::CommitRenderData()
	{
		BOOST_ASSERT(mQueue);
		while (!mQueue->IsEmpty())
		{
			auto ro = mQueue->Pop();

		}
	}

}