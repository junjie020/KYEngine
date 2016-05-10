#ifndef __STATEHELPER_H__
#define __STATEHELPER_H__

#include "Graphic/GraphicDef.h"
namespace KY
{

	class RasterizerStateObj;
	class DepthStencilStateObj;
	class BlendStateObj;
	class SamplerStateObj;

	struct RasterizerState;
	struct DepthStencilState;
	struct BlendState;
	struct SamplerState;

	class RenderOperation;

	class StateHelper
	{
	public:
		StateHelper();
		~StateHelper();

	private:
		template<class StateObjType>
		static StateObjType* InitStateObj(StateObjType* &stateObj, const typename StateObjType::State &state);

	public:
		RasterizerStateObj* InitRasterizerStateObj(const RasterizerState &state);
		DepthStencilStateObj* InitDepthStencilStateObj(const DepthStencilState &state);
		BlendStateObj* InitBlendStateObj(const BlendState &state);

		SamplerStateObj* InitSamplerObj(uint32 idx, const SamplerState &state);

		bool InitPipelineStateObj(const RasterizerState *rsState, const DepthStencilState *dsState, const BlendState *blendState, RenderOperation *ro);
		bool InitPipelineStateObj(RenderOperation *ro);

		bool InitPSSamplerStateObjs(uint32 idx, uint32 count, const SamplerState *sState, RenderOperation *ro);

	private:
		void InitRO(RenderOperation *ro);		

	private:
		RasterizerStateObj*		mRSObj;
		DepthStencilStateObj*	mDSObj;
		BlendStateObj*			mBlendObj;

		SamplerStateObj*		mPSSamplerObjs[MAX_SAMPLER_STATE_NUM];
	};
}
#endif	//__STATEHELPER_H__
