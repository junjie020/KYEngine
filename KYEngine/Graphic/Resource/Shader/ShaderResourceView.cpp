#include "stdafx.h"
#include "ShaderResourceView.h"

#include "Graphic/HI/DX/Shader/Dx11ShaderResourceView.h"

namespace KY
{
	bool ShaderResourceView::Init(const SRVParam &param, Resource *res)
	{
		BOOST_ASSERT(nullptr == mDx11Internal);

		mDx11Internal = new DX::Dx11ShaderResourceView();
		return mDx11Internal->Init(param, res);
	}

}
