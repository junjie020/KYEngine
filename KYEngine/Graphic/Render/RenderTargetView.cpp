#include "stdafx.h"

#include "RenderTargetView.h"

#include "Graphic/HI/DX/Render/Dx11RenderTargetView.h"

namespace KY
{
	bool RenderTargetView::Init(const RTVParam &param, Resource *res)
	{
		BOOST_ASSERT(nullptr == mDx11Internal);

		mDx11Internal = new DX::Dx11RenderTargetView;
		return mDx11Internal->Init(param, res);
	}

}