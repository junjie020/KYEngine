#include "stdafx.h"
#include "PipelineStage.h"

#include "Graphic/HI/DX/Stage/Dx11PipelineStage.h"

namespace KY
{
	void IAStage::SetInputLayout(const InputLayout *il)
	{
		mIA->SetInputLayout(il);
	}

	void IAStage::SetPrimitiveType(PrimitiveType type)
	{
		mIA->SetPrimitiveType(type);
	}

	void IAStage::SetVertexBuffer(const VertexBuffer *vb, const BufferInfo &info)
	{
		mIA->SetVertexBuffer(vb, info);
	}

	void IAStage::SetIndexBuffer(const IndexBuffer *ib, const BufferInfo &info)
	{
		mIA->SetIndexBuffer(ib, info);
	}

	IAStage::IAStage()
	{
		mIA = new DX::Dx11IAStage;
	}

	IAStage::~IAStage()
	{
		SafeDelete(mIA);
	}


	void VSStage::SetShader(const Shader *shader)
	{
		mVS->SetShader(shader);
	}

	void VSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{
		mVS->SetConstBuffer(buffer, info);
	}

	void VSStage::SetSamplerState(uint32 idx, const SamplerStateObj *obj)
	{
		mVS->SetSamplerStates(idx, { obj });
	}

	void VSStage::SetSamplerStates(uint32 idx, const SamplerStateObjConstVec &objs)
	{
		mVS->SetSamplerStates(idx, objs);
	}

	void VSStage::SetShaderResourceView(uint32 idx, const ShaderResourceView *srv)
	{
		mVS->SetShaderResourceViews(idx, {srv});
	}

	void VSStage::SetShaderResourceViews(uint32 idx, const ShaderResourceViewConstVec &srvs)
	{
		mVS->SetShaderResourceViews(idx, srvs);
	}

	VSStage::VSStage()
	{
		mVS = new DX::Dx11VSStage;
	}

	VSStage::~VSStage()
	{
		SafeDelete(mVS);
	}


	void RSStage::SetViewPort(const Viewport *v)
	{
		mRS->SetViewPort(v);
	}

	void RSStage::SetRasterizerState(const RasterizerStateObj *obj)
	{
		mRS->SetRasterizerState(obj);
	}

	RSStage::RSStage()
	{
		mRS = new DX::Dx11RSStage;
	}

	RSStage::~RSStage()
	{
		SafeDelete(mRS);
	}


	void PSStage::SetShader(const Shader *shader)
	{
		mPS->SetShader(shader);
	}

	void PSStage::SetConstBuffer(const Buffer &buffer, const BufferInfo &info)
	{
		mPS->SetConstBuffer(buffer, info);
	}

	void PSStage::SetSamplerState(uint32 idx, const SamplerStateObj *obj)
	{
		mPS->SetSamplerStates(idx, {obj});
	}

	void PSStage::SetSamplerStates(uint32 idx, const SamplerStateObjConstVec &objs)
	{
		mPS->SetSamplerStates(idx, objs);
	}

	void PSStage::SetShaderResourceView(uint32 idx, const ShaderResourceView *srv)
	{
		mPS->SetShaderResourceViews(idx, { srv });
	}

	void PSStage::SetShaderResourceViews(uint32 idx, const ShaderResourceViewConstVec &srvs)
	{
		mPS->SetShaderResourceViews(idx, srvs);
	}

	PSStage::PSStage()
	{
		mPS = new DX::Dx11PSStage;
	}

	PSStage::~PSStage()
	{
		SafeDelete(mPS);
	}


	void OMStage::SetDepthStencilState(const DepthStencilStateObj *obj)
	{
		mOM->SetDepthStencilState(obj);
	}

	void OMStage::SetBlendState(const BlendStateObj *obj)
	{
		mOM->SetBlendState(obj);
	}

	OMStage::OMStage()
	{
		mOM = new DX::Dx11OMStage;
	}

	OMStage::~OMStage()
	{
		SafeDelete(mOM);
	}

}