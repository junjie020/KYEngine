#ifndef _RENDEROPERATION_H_
#define _RENDEROPERATION_H_

#include "Graphic/GraphicDef.h"

namespace KY
{
	class VertexBuffer;
	class IndexBuffer;
	class InputLayout;
	class Shader;

    class RenderOperation
    {
    public:
		RenderOperation()
			: mVertexBuf(nullptr)
			, mIndexBuf(nullptr)
			, mPriType(PT_Unknown)
		{
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
		//@}

		//{@
		void SetIndexBuffer(IndexBuffer *buf, BufferInfo &info){
			mIndexBuf = buf;
			mVertexInfo = info;
		}

		const IndexBuffer* GetIndexBuffer() const { return mIndexBuf; }
		const BufferInfo& GetIndexBufferInfo() const { return mIndexInfo; }
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

	private:
		VertexBuffer *mVertexBuf;
		BufferInfo	mVertexInfo;

		IndexBuffer *mIndexBuf;
		BufferInfo mIndexInfo;

		Shader* mShaders[ShdrT_Count];

		InputLayout *mInputLayout;

		PrimitiveType mPriType;
    };
}
#endif // _RENDEROPERATION_H_