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

	struct Viewport;

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
			: mVertexBuf(nullptr)
			, mIndexBuf(nullptr)
			, mInputLayout(nullptr)
			, mRSStateObj(nullptr)
			, mDepthStencilStateObj(nullptr)
			, mBlendStateObj(nullptr)
			, mViewport(nullptr)			
			, mPriType(PT_Unknown)
		{
			ZERO_MEMORY(miDrawParam); // ZERO_MEMORY(vDrawParam);
			ZERO_MEMORY(mShaders);
		}
		~RenderOperation(){}

		//{@
		void SetVertexBuffer(VertexBuffer *buf, BufferInfo &info){
			mVertexBuf = buf;
			mVertexInfo = info;
		}

		const VertexBuffer* GetVertexBuffer() const { return mVertexBuf; }
		const BufferInfo& GetVertexBufferInfo() const { return mVertexInfo; }
		void SetVertexDrawInfo(const DrawVertexBufferParam &vparam) { mvDrawParam = vparam; }
		const DrawVertexBufferParam& GetVertexDrawInfo() const { return mvDrawParam; }
		//@}

		//{@
		void SetIndexBuffer(IndexBuffer *buf, BufferInfo &info){
			mIndexBuf = buf;
			mVertexInfo = info;
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

		//{@
		const Viewport* GetViewport() const {
			return mViewport;
		}

		void SetViewport(const Viewport *vp){
			mViewport = vp;
		}
		//@}

	private:
		union{
			DrawVertexBufferParam	mvDrawParam;
			DrawIndexBufferParam	miDrawParam;
		};

		VertexBuffer *mVertexBuf;
		BufferInfo	mVertexInfo;

		IndexBuffer *mIndexBuf;
		BufferInfo mIndexInfo;

		Shader* mShaders[ShdrT_Count];

		InputLayout *mInputLayout;

		RasterizerStateObj*		mRSStateObj;
		DepthStencilStateObj*	mDepthStencilStateObj;
		BlendStateObj*			mBlendStateObj;

		const Viewport *mViewport;
		PrimitiveType	mPriType;
    };
}
#endif // _RENDEROPERATION_H_