#include "stdafx.h"

#include "StateHelper.h"

#include "StateObject.h"
#include "StateObject.inl"
#include "Graphic/Render/RenderOperation.h"

#include "DebugUtils/TraceUtils.h"

namespace KY
{

	StateHelper::StateHelper() 
		: mRSObj(nullptr)
		, mDSObj(nullptr)
		, mBlendObj(nullptr)
	{

	}

	StateHelper::~StateHelper()
	{
		SafeDelete(mRSObj);
		SafeDelete(mDSObj);
		SafeDelete(mBlendObj);
	}

	template<class StateObjType>
	StateObjType* StateHelper::InitStateObj(StateObjType* &stateObj, const typename StateObjType::State &state)
	{
		SafeDelete(stateObj);
		stateObj = new StateObjType;
		if (!stateObj->CreateObj(state))
		{
			DebugOutline("create state failed!");
			delete stateObj;
			stateObj = nullptr;
		}

		return stateObj;
	}

	RasterizerStateObj* StateHelper::InitRasterizerStateObj(const RasterizerState &state)
	{
		return InitStateObj(mRSObj, state);
	}

	DepthStencilStateObj* StateHelper::InitDepthStencilStateObj(const DepthStencilState &state)
	{
		return InitStateObj(mDSObj, state);
	}

	BlendStateObj* StateHelper::InitBlendStateObj(const BlendState &state)
	{
		return InitStateObj(mBlendObj, state);
	}

	SamplerStateObj* StateHelper::InitSamplerObj(uint32 idx, const SamplerState &state)
	{
		return InitStateObj(mSamplerObjs[idx], state);
	}

	bool StateHelper::InitPipelineStateObj(RenderOperation *ro)
	{
		InitRasterizerStateObj(RasterizerState());
		InitDepthStencilStateObj(DepthStencilState());
		InitBlendStateObj(BlendState());

		if (ro)
			InitRO(ro);

		return true;
	}

	bool StateHelper::InitPipelineStateObj(const RasterizerState *rsState, const DepthStencilState *dsState, const BlendState *blendState, RenderOperation *ro)
	{
		if (rsState)
			InitRasterizerStateObj(*rsState);

		if (dsState)
			InitDepthStencilStateObj(*dsState);

		if (blendState)
			InitBlendStateObj(*blendState);

		if (ro)
			InitRO(ro);

		return true;
	}

	bool StateHelper::InitSamplerStateObjs(uint32 idx, uint32 count, const SamplerState *sState, RenderOperation *op)
	{
		while (idx < count)
		{
			const SamplerState *ss = sState + idx;
			if (ss)
			{
				auto obj = InitSamplerObj(idx, *ss);

				op->SetSamplerState(idx, obj);
			}
		}

		return true;
	}

	void StateHelper::InitRO(RenderOperation *ro)
	{
		if (mRSObj)
			ro->SetRasterizerStateObj(mRSObj);

		if (mDSObj)
			ro->SetDepthStencilStateObj(mDSObj);

		if (mBlendObj)
			ro->SetBlendStateObj(mBlendObj);
	}

}