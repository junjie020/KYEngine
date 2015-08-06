#ifndef _STATEOBJECT_INL_
#define _STATEOBJECT_INL_

#include "Graphic/GraphicDef.h"

#include "Graphic/DX/Dx11StateObject.h"
namespace KY
{

	template<class StateType, class InternalType>
	KY::StateObj<StateType, InternalType>::~StateObj()
	{
		SafeDelete(mInternalObj);
	}

	template<class StateType, class InternalType>
	bool KY::StateObj<StateType, InternalType>::CreateObj(const State &s)
	{
		if (nullptr == mInternalObj)
			mInternalObj = new InternalType;

		return mInternalObj->Create(s);		
	}

	template<class StateType, class InternalType>
	bool KY::StateObj<StateType, InternalType>::IsValid() const
	{
		return mInternalObj->IsValid();
	}


}
#endif //_STATEOBJECT_INL_