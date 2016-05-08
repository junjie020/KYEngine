#include "stdafx.h"
#include "ShaderResourceView.h"

#include "Graphic/HI/DX/Shader/Dx11ShaderResourceView.h"

namespace KY
{
	

	ShaderResourceView::~ShaderResourceView()
	{
		SafeDelete(mSRV);
	}

	bool ShaderResourceView::Init(const SRVParam &param, Resource *res)
	{
		BOOST_ASSERT(nullptr == mSRV);

		mSRV = new DX::Dx11ShaderResourceView();
		return mSRV->Init(param, res);
	}

}
