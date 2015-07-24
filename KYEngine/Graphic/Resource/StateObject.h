#ifndef _STATEOBJECT_H_
#define _STATEOBJECT_H_

#include "Graphic/GraphicDef.h"

namespace KY
{
	namespace DX
	{
		class Dx11RasterizerStateObj;
		class Dx11BlendStateObj;
		class Dx11DepthStencilStateObj;
	}

	template<class StateType, class InternalType>
	class StateObj
	{
	public:
		typedef StateType State;
		StateObj() : mInternalObj(nullptr){}
		~StateObj();
		bool CreateObj(const State &s);
		
	protected:
		InternalType *mInternalObj;
	};

	typedef StateObj<RasterizerState, DX::Dx11RasterizerStateObj>		RasterizerStateObj;
	typedef StateObj<BlendState, DX::Dx11BlendStateObj>					BlendStateObj;
	typedef StateObj<DepthStencilState, DX::Dx11DepthStencilStateObj>	DepthStencilStateObj;

	//class RasterizerStateObj : public StateObj<RasterizerState>
	//{
	//public:
	//	void CreateObj(const RasterizerState &state);
	//private:
	//	DX::Dx11RasterizerStateObj *mInternalObj;
	//};

	//class BlendStateObj
	//{
	//public:
	//	void CreateObj(const BlendState &state);
	//private:
	//	DX::Dx11RasterizerStateObj *mInternalObj;
	//};

	//class DepthStencilStateObj
	//{
	//public:
	//	void CreateObj(const DepthStencilState &state);
	//};
}
#endif //_STATEOBJECT_H_