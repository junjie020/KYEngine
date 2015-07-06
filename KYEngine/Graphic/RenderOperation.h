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

		void SetVertexBuffer(VertexBuffer *buf){

		}

		void SetIndexBuffer(IndexBuffer *buf){

		}
	private:
		VertexBuffer *mVertexBuf;
		IndexBuffer *mIndexBuf;
    };
}
#endif // _RENDEROPERATION_H_