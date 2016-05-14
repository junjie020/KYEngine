#include "stdafx.h"

#include "RenderTargetView.h"

#include "Graphic/HI/DX/Render/Dx11RenderTargetView.h"

namespace KY
{
	RenderTargetView::~RenderTargetView()
	{
		SafeDelete(mRTV);
	}

	bool RenderTargetView::Init(const RTVParam &param, Resource *res)
	{
		BOOST_ASSERT(nullptr == mRTV);

		mRTV = new DX::Dx11RenderTargetView;

		return mRTV->Init(param, res);
	}

}