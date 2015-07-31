#include "stdafx.h"

#include "Dx11PipelineStage.h"
#include "Graphic/DX/Dx11.h"


#include "Graphic/Graphic.h"

namespace KY
{
	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11IAStage::SetInputLayout(const InputLayout *il)
	{
		auto dx11 = Graphic::Inst()->GetDx11();
		auto context = dx11->GetDeviceContext();
		BOOST_ASSERT(context);


	}

	void DX::Dx11IAStage::SetPrimitiveType(PrimitiveType pt)
	{

	}

	void DX::Dx11IAStage::SetVertexBuffer(const VertexBuffer *vb, const BufferInfo &info)
	{

	}

	void DX::Dx11IAStage::SetIndexBuffer(const IndexBuffer *ib, const BufferInfo &info)
	{

	}

	//////////////////////////////////////////////////////////////////////////

	void DX::Dx11VSStage::SetShader(const Shader *shader)
	{

	}

	void DX::Dx11VSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11RSStage::SetViewPort(Viewport *vp)
	{

	}

	void DX::Dx11RSStage::SetRasterizerState(const RasterizerStateObj *obj)
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11PSStage::SetShader(const Shader *shader)
	{

	}

	void DX::Dx11PSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11OMStage::SetDepthStencilState(const DepthStencilStateObj *obj)
	{

	}

	void DX::Dx11OMStage::SetBlendState(const BlendStateObj *obj)
	{

	}

}