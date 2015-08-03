#include "stdafx.h"

#include "Dx11PipelineStage.h"
#include "Graphic/DX/Dx11.h"


#include "Graphic/Graphic.h"

#include "Graphic/Viewport.h"

#include "Graphic/Resource/Shader.h"
#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/DX/Buffer/DX11VertexBuffer.h"

#include "Graphic/Resource/IndexBuffer.h"
#include "Graphic/DX/Buffer/DX11IndexBuffer.h"

#include "Graphic/Resource/Buffer.h"


#include "Graphic/DX/Buffer/Dx11Shader.h"
#include "Graphic/DX/DX11NameTranslator.h"

#include "Graphic/Resource/StateObject.h"
#include "Graphic/Resource/StateObject.inl"
#include "Graphic/DX/Dx11StateObject.h"


namespace KY
{
	//////////////////////////////////////////////////////////////////////////

#define GET_CONTEXT() 		Graphic::Inst()->GetDx11()->GetDeviceContext()
	
	void DX::Dx11IAStage::SetInputLayout(const InputLayout *il)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->IASetInputLayout(il->GetInternal()->GetInternal());
	}

	void DX::Dx11IAStage::SetPrimitiveType(PrimitiveType pt)
	{		
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->IASetPrimitiveTopology(DX11NameTranslator::Inst()->ToPrimitiveTopology(pt));
	}

	void DX::Dx11IAStage::SetVertexBuffer(const VertexBuffer *vb, const BufferInfo &info)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		auto d3d11buffer = vb->GetInternal()->GetInternal();
		context->IASetVertexBuffers(info.slotIdx, 1, &d3d11buffer, &info.strides, &info.offset);
	}

	void DX::Dx11IAStage::SetIndexBuffer(const IndexBuffer *ib, const BufferInfo &info)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		auto d3d11buffer = ib->GetInternal()->GetInternal();

		BOOST_ASSERT(info.strides == 16 || info.strides == 32);
		context->IASetIndexBuffer(d3d11buffer, info.strides == 16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, info.offset);
	}

	//////////////////////////////////////////////////////////////////////////

	void DX::Dx11VSStage::SetShader(const Shader *shader)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);


		auto dx11Shader = shader->GetInternal();
		auto d3dshader = dx11Shader->GetInternal<ID3D11VertexShader>();

		//auto linkage = dx11Shader->GetClassLinkage();
		context->VSSetShader(d3dshader, nullptr, 0);
	}

	void DX::Dx11VSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);
		auto dx11Buf = buffer.GetInternal()->GetInternal();
		context->VSSetConstantBuffers(info.slotIdx, 1, &dx11Buf);
	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11RSStage::SetViewPort(const Viewport *vp)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		D3D11_VIEWPORT vpd3d = 
		{
			float(vp->mRect.left), float(vp->mRect.top), 
			float(vp->mRect.width()), float(vp->mRect.height()), 
			vp->mDepthRange.beg,  vp->mDepthRange.end,
		};
		context->RSSetViewports(1, &vpd3d);
	}

	void DX::Dx11RSStage::SetRasterizerState(const RasterizerStateObj *obj)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->RSSetState(obj->GetInternal()->GetInternal());
	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11PSStage::SetShader(const Shader *shader)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->PSSetShader(shader->GetInternal()->GetInternal<ID3D11PixelShader>(), nullptr, 0);
	}

	void DX::Dx11PSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		auto d3dBuffer = buffer.GetInternal()->GetInternal();
		context->PSSetConstantBuffers(info.slotIdx, 1, &d3dBuffer);
	}

	//////////////////////////////////////////////////////////////////////////
	void DX::Dx11OMStage::SetDepthStencilState(const DepthStencilStateObj *obj)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->OMSetDepthStencilState(obj->GetInternal()->GetInternal(), obj->GetStencilRef());
	}

	void DX::Dx11OMStage::SetBlendState(const BlendStateObj *obj)
	{
		auto context = GET_CONTEXT();
		BOOST_ASSERT(context);

		context->OMSetBlendState(obj->GetInternal()->GetInternal(),
			reinterpret_cast<const float*>(&obj->GetBlendFactor()),
			obj->GetSampleMask());
	}

}