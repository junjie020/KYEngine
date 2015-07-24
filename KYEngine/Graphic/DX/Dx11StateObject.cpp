#include "stdafx.h"

#include "Dx11StateObject.h"

namespace KY
{
	

	bool DX::Dx11RasterizerStateObj::Create(const RasterizerState &state)
	{
		return true;
	}


	bool DX::Dx11BlendStateObj::Create(const BlendState &state)
	{
		return true;
	}


	bool DX::Dx11DepthStencilStateObj::Create(const DepthStencilState &state)
	{
		return true;
	}

}