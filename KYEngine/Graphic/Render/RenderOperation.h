#ifndef _RENDEROPERATION_H_
#define _RENDEROPERATION_H_

#include "Graphic/GraphicDef.h"

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

	using ShaderResourceViewVec = std::vector<ShaderResourceView*>;

	class RenderOperation
	{
	public:
		RenderOperation()
			: mIndexBuf(nullptr)
			, mInputLayout(nullptr)
			, mRSStateObj(nullptr)
			, mDepthStencilStateObj(nullptr)
			, mBlendStateObj(nullptr)			
			, mPriType(PT_Unknown)
		{
			ZERO_MEMORY(miDrawParam); // ZERO_MEMORY(vDrawParam);
			ZERO_MEMORY(mShaders);
			ZERO_MEMORY(mSamplerStateoObjs);
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
		size_t GetVertexBufferInfoCount() const { return mVBIs.size(); }
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
		void SetSamplerState(uint32 idx, SamplerStateObj *stateObj) {
			mSamplerStateoObjs[idx] = stateObj;
		}

		void SetSamplerState(uint32 idx, uint32 count, SamplerStateObj *stateObj) {
			BOOST_ASSERT((idx + count) < COUNT_OF(mSamplerStateoObjs));
			memcpy(mSamplerStateoObjs[idx], stateObj, count);
		}

		SamplerStateObj* GetSamplerObj(uint32 idx) const {
			return mSamplerStateoObjs[idx];
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
		//@}


		//{@
		void SetShader(Shader *shader, ShaderType type){
			BOOST_ASSERT(0 <= type && type < ShdrT_Count);
			mShaders[type] = shader;
		}

		const Shader* GetShader(ShaderType type) const {
			BOOST_ASSERT(0 <= type && type < ShdrT_Count);
			return mShaders[type];
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

		Shader* mShaders[ShdrT_Count];

		InputLayout *mInputLayout;

		RasterizerStateObj*		mRSStateObj;
		DepthStencilStateObj*	mDepthStencilStateObj;
		BlendStateObj*			mBlendStateObj;

		ShaderResourceViewVec	mVSSRV;
		ShaderResourceViewVec	mPSSRV;
		
		SamplerStateObj*		mSamplerStateoObjs[MAX_SAMPLER_STATE_NUM];

		PrimitiveType	mPriType;
    };
}
#endif // _RENDEROPERATION_H_