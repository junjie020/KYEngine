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

		struct BufferInfo{
			uint32 startIdx;
			uint32 elemNum;
		};

		void SetVertexBuffer(VertexBuffer *buf, BufferInfo &info){
			mVertexBuf = buf;
			mVertexInfo = info;
		}

		void SetIndexBuffer(IndexBuffer *buf, BufferInfo &info){
			mIndexBuf = buf;
			mVertexInfo = info;
		}

		void SetInputLayout(InputLayout *il){
			mInputLayout = il;
		}

		void SetShader(Shader *shader, ShaderType type){
			BOOST_ASSERT(0 <= type && type < ShdrT_Count);
			mShaders[type] = shader;
		}

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