#ifndef _RENDEROPERATION_H_
#define _RENDEROPERATION_H_

#include "Graphic/GraphicDef.h"
#include "Graphic/GraphicDataDef.h"

namespace KY
{
	class VertexBuffer;
	class IndexBuffer;
	class InputLayout;
	class Shader;


	class RasterizerStateObj;
	class DepthStencilStateObj;
	class BlendStateObj;
	class SamplerStateObj;

	class ShaderResourceView;

	class Viewport;

	struct DrawVertexBufferParam{		
		uint32 mVertexCount;
		uint32 mStartVertexLocation;
	};

	struct DrawIndexBufferParam{
		uint32 mIndexCount;
		uint32 mStartIndexLocation;
		uint32 mBaseVertexLocation;
	};

	class RenderOperation
	{
	public:
		RenderOperation()
			: mIndexBuf(nullptr)
			, mInputLayout(nullptr)
			, mRSStateObj(nullptr)
			, mDepthStencilStateObj(nullptr)
			, mBlendStateObj(nullptr)			
			, mPriType(PrimitiveType::PT_Unknown)
		{
			ZERO_MEMORY(miDrawParam); // ZERO_MEMORY(vDrawParam);
			ZERO_MEMORY(mShaders);
			ZERO_MEMORY(mVSSamplerStateoObjs);
			ZERO_MEMORY(mPSSamplerStateoObjs);
		}
		~RenderOperation(){}

		//{@

		struct VertexBufferInfo{
			VertexBuffer *mVertexBuf;
			BufferInfo	mVertexInfo;
		};

		typedef std::vector<VertexBufferInfo> VBIVec;

		void AddVertexBuffer(VertexBuffer *buf, BufferInfo &info){			
			mVBIs.push_back({buf, info});
		}

		const VertexBufferInfo& GetVertexBufferInfo(uint32 idx) const { return mVBIs[idx]; }
		uint32 GetVertexBufferInfoCount() const { return uint32(mVBIs.size()); }
		const VBIVec& GetVertexBufferInfos() const { return mVBIs; }
		
		void SetVertexDrawInfo(const DrawVertexBufferParam &vparam) { mvDrawParam = vparam; }
		const DrawVertexBufferParam& GetVertexDrawInfo() const { return mvDrawParam; }
		//@}

		//{@
		void SetIndexBuffer(IndexBuffer *buf, BufferInfo &info){
			mIndexBuf = buf;
			mIndexInfo = info;
		}

		const IndexBuffer* GetIndexBuffer() const { return mIndexBuf; }
		const BufferInfo& GetIndexBufferInfo() const { return mIndexInfo; }

		void SetIndexDrawInfo(const DrawIndexBufferParam &iparam) { miDrawParam = iparam; }
		const DrawIndexBufferParam& GetIndexDrawInfo() const { return miDrawParam; }
		//@}

		//{@
		void SetInputLayout(InputLayout *il){
			mInputLayout = il;
		}

		const InputLayout* GetInputLayout() const{
			return mInputLayout;
		}
		//@}

		//{@
		void SetVSSamplerState(uint32 idx, SamplerStateObj *stateObj) {
			mVSSamplerStateoObjs[idx] = stateObj;
		}

		void SetVSSamplerState(uint32 idx, uint32 count, SamplerStateObj *stateObj) {
			BOOST_ASSERT((idx + count) < COUNT_OF(mVSSamplerStateoObjs));
			memcpy(mVSSamplerStateoObjs[idx], stateObj, count);
		}

		SamplerStateObj* GetVSSamplerObj(uint32 idx) const {
			return mVSSamplerStateoObjs[idx];
		}

		SamplerStateObj** GetVSSamplerObjs() const {
			return (SamplerStateObj**)mVSSamplerStateoObjs;
		}

		void SetPSSamplerState(uint32 idx, SamplerStateObj *stateObj) {
			mPSSamplerStateoObjs[idx] = stateObj;
		}

		void SetPSSamplerState(uint32 idx, uint32 count, SamplerStateObj *stateObj) {
			BOOST_ASSERT((idx + count) < COUNT_OF(mPSSamplerStateoObjs));
			memcpy(mPSSamplerStateoObjs[idx], stateObj, count);
		}

		SamplerStateObj* GetPSSamplerObj(uint32 idx) const {
			return mPSSamplerStateoObjs[idx];
		}

		SamplerStateObj** GetPSSamplerObjs() const {
			return (SamplerStateObj**)mPSSamplerStateoObjs;
		}

		void SetShaderResourceView(uint32 idx, ShaderResourceView *srv, ShaderResourceViewVec &srvs){
			if (idx < srvs.size()) {
				srvs[idx] = srv;
				return;
			}

			for (size_t ii = srvs.size(); ii < idx; ++ii)
			{
				srvs.push_back(nullptr);
			}

			srvs.push_back(srv);
		}

		void SetVSShaderResourceView(uint32 idx, ShaderResourceView *srv) {
			SetShaderResourceView(idx, srv, mVSSRV);
		}

		void SetPSShaderResourceView(uint32 idx, ShaderResourceView *srv) {
			SetShaderResourceView(idx, srv, mPSSRV);
		}

		ShaderResourceView* GetVSShaderResourceView(uint32 idx) const {
			BOOST_ASSERT(idx < mVSSRV.size());
			return mVSSRV[idx];
		}

		const ShaderResourceViewVec& GetVSShaderResourceViews() const {
			return mVSSRV;
		}

		ShaderResourceView* GetPSShaderResourceView(uint32 idx) const {
			BOOST_ASSERT(idx < mPSSRV.size());
			return mPSSRV[idx];
		}

		const ShaderResourceViewVec& GetPSShaderResourceViews() const {
			return mPSSRV;
		}
		//@}


		//{@
		void SetShader(Shader *shader, ShaderType type){
			BOOST_ASSERT(0 <= uint32(type) && uint32(type) < uint32(ShaderType::Count));
			mShaders[uint32(type)] = shader;
		}

		const Shader* GetShader(ShaderType type) const {
			BOOST_ASSERT(0 <= uint32(type) && uint32(type) < uint32(ShaderType::Count));
			return mShaders[uint32(type)];
		}
		//@}

		//{@
		void SetPrimitiveType(PrimitiveType type){
			mPriType = type;
		}

		PrimitiveType GetPrimitiveType() const {
			return mPriType;
		}
		//@}

		//{@
		RasterizerStateObj* GetRasterizerStateObj() const {
			return mRSStateObj;
		}

		void SetRasterizerStateObj(RasterizerStateObj *obj){
			mRSStateObj = obj;
		}

		DepthStencilStateObj* GetDepthStencilStateObj() const{
			return mDepthStencilStateObj;
		}
		
		void SetDepthStencilStateObj(DepthStencilStateObj* obj){
			mDepthStencilStateObj = obj;
		}

		BlendStateObj* GetBlendStateObj() const {
			return mBlendStateObj;
		}

		void SetBlendStateObj(BlendStateObj *obj){
			mBlendStateObj = obj;
		}
		//@}

	private:
		union{
			DrawVertexBufferParam	mvDrawParam;
			DrawIndexBufferParam	miDrawParam;
		};

		
		VBIVec	mVBIs;	

		IndexBuffer *mIndexBuf;
		BufferInfo mIndexInfo;

		Shader* mShaders[int32(ShaderType::Count)];

		InputLayout *mInputLayout;

		RasterizerStateObj*		mRSStateObj;
		DepthStencilStateObj*	mDepthStencilStateObj;
		BlendStateObj*			mBlendStateObj;

		ShaderResourceViewVec	mVSSRV;
		ShaderResourceViewVec	mPSSRV;
		
		SamplerStateObj*		mVSSamplerStateoObjs[MAX_SAMPLER_STATE_NUM];
		SamplerStateObj*		mPSSamplerStateoObjs[MAX_SAMPLER_STATE_NUM];

		PrimitiveType	mPriType;
    };
}
#endif // _RENDEROPERATION_H_