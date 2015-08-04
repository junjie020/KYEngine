////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Graphic.h"
#include "DX/Dx11.h"
#include "Common/CommonUtils.h"
#include "Graphic/RenderCommandQueue.h"
#include "Graphic/RenderOperation.h"
namespace KY
{
	Graphic::Graphic()
		: mDx(nullptr)
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

			//{@ input asm
			{
				IAStage* ia = GetStage<IAStage>(true);

				auto vb = ro->GetVertexBuffer();
				BOOST_ASSERT(vb);
				ia->SetVertexBuffer(vb, ro->GetVertexBufferInfo());
				ia->SetIndexBuffer(ro->GetIndexBuffer(), ro->GetIndexBufferInfo());
				ia->SetPrimitiveType(ro->GetPrimitiveType());
				ia->SetInputLayout(ro->GetInputLayout());
			}
			//@}

			//{@	vertex
			{
				VSStage* vs = GetStage<VSStage>(true);
				vs->SetShader(ro->GetShader(ShdrT_Vertex));
			}
			//@}

			//{@	rasterizer
			{
				RSStage* rs = GetStage<RSStage>(true);
				auto obj = ro->GetRasterizerStateObj();
				if (obj)
					rs->SetRasterizerState(obj);

				auto vp = ro->GetViewport();
				if (vp)
					rs->SetViewPort(vp);
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

}