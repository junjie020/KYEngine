#ifndef _STATEOBJECT_H_
#define _STATEOBJECT_H_

#include "Graphic/GraphicDef.h"
#include "Math/Vector4.h"
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
		bool IsValid() const;

		InternalType* GetInternal() const { return mInternalObj;  }
		
	protected:
		///-----Hardware object should cache in a singleton object
		InternalType *mInternalObj;
	};

	class RasterizerStateObj : public StateObj<RasterizerState, DX::Dx11RasterizerStateObj>
	{
	public:

	};

	class BlendStateObj : public StateObj<BlendState, DX::Dx11BlendStateObj>
	{
	public:
		BlendStateObj() : mBlendFactor(0.0f, 0.0f, 0.0f, 0.0f), mSampleMask(0xFFFFFFFF){}

	public:
		//{@ modify in runtime
		const Vec4f& GetBlendFactor() const { return mBlendFactor; }
		void		 SetBlendFactor(const Vec4f& bf) { mBlendFactor = bf; }

		uint32		GetSampleMask() const { return mSampleMask; }
		void		SetSampleMask(uint32 mask) { mSampleMask = mask; }
		//@}
	private:
		Vec4f		mBlendFactor;
		uint32		mSampleMask;
	};

	class DepthStencilStateObj : public StateObj<DepthStencilState, DX::Dx11DepthStencilStateObj>
	{
	public:
		DepthStencilStateObj() : mStencilRef(0){}

		uint32	GetStencilRef() const { return mStencilRef; }
		void	SetStencilRef(uint32 ref) { mStencilRef = ref; }
	private:
		uint32 mStencilRef;
	};

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