#ifndef _RENDEROPERATION_H_
#define _RENDEROPERATION_H_

namespace KY
{
	class VertexBuffer;
	class IndexBuffer;
    class RenderOperation
    {
    public:
		RenderOperation()
			: mVertexBuf(nullptr)
			, mIndexBuf(nullptr)
		{

		}
		~RenderOperation(){

		}

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
	private:
		VertexBuffer *mVertexBuf;
		BufferInfo	mVertexInfo;

		IndexBuffer *mIndexBuf;
		BufferInfo mIndexInfo;
    };
}
#endif // _RENDEROPERATION_H_