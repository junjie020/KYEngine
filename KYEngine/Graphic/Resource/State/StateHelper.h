#ifndef __STATEHELPER_H__
#define __STATEHELPER_H__

namespace KY
{

	class RasterizerStateObj;
	class DepthStencilStateObj;
	class BlendStateObj;

	struct RasterizerState;
	struct DepthStencilState;
	struct BlendState;

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

		bool Init(const RasterizerState *rsState, const DepthStencilState *dsState, const BlendState *blendState, RenderOperation *ro);
		bool Init(RenderOperation *ro);

	private:
		void InitRO(RenderOperation *ro);		

	private:
		RasterizerStateObj*		mRSObj;
		DepthStencilStateObj*	mDSObj;
		BlendStateObj*			mBlendObj;
	};
}
#endif	//__STATEHELPER_H__
