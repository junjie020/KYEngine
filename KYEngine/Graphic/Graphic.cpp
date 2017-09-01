////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Graphic.h"
#include "Graphic/HI/DX/Dx11.h"
#include "Common/CommonUtils.h"
#include "Graphic/Render/RenderCommandQueue.h"
#include "Graphic/Render/RenderOperation.h"
#include "Graphic/Resource/Shader/Shader.h"

#include "Graphic/Render/WindowRenderTarget.h"
#include "Graphic/Render/Viewport.h"
#include "Graphic/Material/GlobalConstBuffer.h"


namespace KY
{
	Graphic::Graphic()
		: mDx(nullptr)
		, mGlobalConstBuffer()
	{
		ZERO_MEMORY(mStages);
	}


	Graphic::~Graphic()
	{
		SafeDelete(mDx);		
		//{@
		std::for_each(std::begin(mStages), std::end(mStages), [](PipelineStage *stage){ if (stage) delete stage; });
		ZERO_MEMORY(mStages);
		//@}
	}


	bool Graphic::Initialize(const GraphicInitParam &param)
	{
		mInitParam = param;
		SafeDelete(mDx);
		mDx = new DX::Dx11;

		if (mDx->Init(param))
		{
			mInitParam.featureLevel = mDx->GetSelectedFeatureLevel();
			return true;
		}

		return false;
	}


	void Graphic::Shutdown()
	{
		SafeDelete(mDx);
		if (!mRenderTargets.empty())
		{
			BOOST_ASSERT(false && "render target container is not empty, need to call DestoryViewport/DestoryRenderTexture function when not using the render target");
		}
		return;
	}

	bool Graphic::CommitRenderCommands()
	{
		mDx->Swap();
		if (mDx->Prepare())
		{
			CommitRenderData();
			return true;
		}

		return false;
	}

	void Graphic::CommitRenderData()
	{
		for (auto target : mRenderTargets)
		{
			auto& queue = target->GetRenderQueue();

			RSStage* rs = GetStage<RSStage>(true);
			rs->SetViewPort(static_cast<Viewport *>(target));

			while (!queue.IsEmpty())
			{
				auto ro = queue.Pop();

				//{@ input asm
				IAStage* ia = GetStage<IAStage>(true);

				const uint32 numVB = ro->GetVertexBufferInfoCount();
				for (auto iVB = 0U; iVB < numVB; ++iVB)
				{
					const auto& vbi = ro->GetVertexBufferInfo(iVB);
					BOOST_ASSERT(vbi.mVertexBuf);
					ia->SetVertexBuffer(vbi.mVertexBuf, vbi.mVertexInfo);
				}

				{
					ia->SetIndexBuffer(ro->GetIndexBuffer(), ro->GetIndexBufferInfo());
					ia->SetPrimitiveType(ro->GetPrimitiveType());
					ia->SetInputLayout(ro->GetInputLayout());
				}
				//@}

				//{@	vertex
				{
					VSStage* vs = GetStage<VSStage>(true);
					auto vsShader = ro->GetShader(ShaderType::ShdrT_Vertex);
					vs->SetShader(vsShader);

					const auto& buffers = vsShader->GetConstBuffers();

					for (auto &bb : buffers)
					{						
						const BufferInfo info = { 0, 0, bb.first };	// hard code offset and strides
						vs->SetConstBuffer(*(bb.second), info);					
					}

					auto samples = ro->GetVSSamplerObjs();
					SamplerStateObjConstVec sampleVec(MAX_SAMPLER_STATE_NUM);
					memcpy(&sampleVec[0], samples, MAX_SAMPLER_STATE_NUM * sizeof(SamplerStateObj*));
					vs->SetSamplerStates(0, sampleVec);

					auto srvs = ro->GetVSShaderResourceViews();
					vs->SetShaderResourceViews(0, ShaderResourceViewConstVec(srvs.begin(), srvs.end()));
				}
				//@}

				//{@	rasterizer
				{				
					auto obj = ro->GetRasterizerStateObj();
					if (obj)
						rs->SetRasterizerState(obj);
				}
				//@}

				//{@	pixel stage
				{
					PSStage *ps = GetStage<PSStage>(true);
					auto psShader = ro->GetShader(ShaderType::ShdrT_Pixel);

					ps->SetShader(psShader);

					const auto& buffers = psShader->GetConstBuffers();

					for (auto &bb : buffers)
					{
						const BufferInfo info = { 0, 0, bb.first };	// hard code offset and strides
						ps->SetConstBuffer(*(bb.second), info);

					}

					auto samples = ro->GetPSSamplerObjs();
					SamplerStateObjConstVec sampleVec(MAX_SAMPLER_STATE_NUM);
					memcpy(&sampleVec[0], samples, MAX_SAMPLER_STATE_NUM * sizeof(SamplerStateObj*));
					ps->SetSamplerStates(0, sampleVec);

					auto srvs = ro->GetPSShaderResourceViews();
					ps->SetShaderResourceViews(0, ShaderResourceViewConstVec(srvs.begin(), srvs.end()));
				}
				//@}

				//{@	output merage
				{
					OMStage* om = GetStage<OMStage>(true);

					auto dsobj = ro->GetDepthStencilStateObj();
					if (dsobj)
						om->SetDepthStencilState(dsobj);

					auto blendobj = ro->GetBlendStateObj();
					if (blendobj)
						om->SetBlendState(blendobj);
				}
				//@}

				auto context = GetDx11()->GetDeviceContext();

				if (ro->GetIndexBuffer())
				{
					auto idxParam = ro->GetIndexDrawInfo();
					context->DrawIndexed(idxParam.mIndexCount, idxParam.mStartIndexLocation, idxParam.mBaseVertexLocation);
				}
				else
				{
					auto vtxParam = ro->GetVertexDrawInfo();
					context->Draw(vtxParam.mVertexCount, vtxParam.mStartVertexLocation);
				}
			}
		}
		
	}
	template<class StageClass>
	StageClass* Graphic::GetStage(bool bInit)
	{
		StageClass* stage = static_cast<StageClass*>(mStages[StageClass::Type]);
		if (nullptr != stage)
			return stage;

		if (bInit)
		{
			stage = new StageClass;
			mStages[StageClass::Type] = stage;
		}
		
		return stage;
	}

	PipelineStage* Graphic::GetStage(StageType type, bool bInit /*= false*/)
	{
		switch (type)
		{
		case ST_IA: return GetStage<IAStage>(bInit);
		case ST_VS: return GetStage<VSStage>(bInit);
		case ST_HS: return GetStage<HSStage>(bInit);
		case ST_TS: return GetStage<TSStage>(bInit);
		case ST_DS: return GetStage<DSStage>(bInit);
		case ST_GS: return GetStage<GSStage>(bInit);
		case ST_SO: return GetStage<SOStage>(bInit);
		case ST_RS: return GetStage<RSStage>(bInit);
		case ST_PS: return GetStage<PSStage>(bInit);
		case ST_OM: return GetStage<OMStage>(bInit);
		default:
			BOOST_ASSERT(false && "not support stage type");
			return nullptr;
		}
	}

	Viewport* Graphic::CreateViewport(const RectI &rt, const Range2F &r)
	{
		Viewport *vp = new Viewport(rt, r);

		mRenderTargets.push_back(vp);
		return vp;
	}

	void Graphic::DestoryViewport(Viewport *vp)
	{
		auto found = std::find(std::begin(mRenderTargets), std::end(mRenderTargets), vp);
		if (found != std::end(mRenderTargets))
			mRenderTargets.erase(found);
	}

	WindowRenderTarget* Graphic::CreateWindowRenderTarget(const RectI &rt)
	{
		WindowRenderTarget *wrt = new WindowRenderTarget(rt);
		mRenderTargets.push_back(wrt);

		return wrt;
	}

	void Graphic::DestoryRenderTarget(WindowRenderTarget *rt)
	{
		auto found = std::find(std::begin(mRenderTargets), std::end(mRenderTargets), rt);
		if (found != std::end(mRenderTargets))
			mRenderTargets.erase(found);
	}

}