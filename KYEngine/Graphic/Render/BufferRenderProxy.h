#pragma once
namespace KY
{
	class VertexBuffer;
	class IndexBuffer;
	class Buffer;
	class BufferRenderProxy
	{
	public:
		BufferRenderProxy()
			: mVertexBuf(nullptr)
			, mIndexBuf(nullptr)
			, mInputLayout(nullptr)
			, mConstBuffer(nullptr)
		{}

		VertexBuffer	*mVertexBuf;
		IndexBuffer		*mIndexBuf;
		InputLayout		*mInputLayout;

		Buffer			*mConstBuffer;

		BufferInfo		mVertexBufferInfo;
		BufferInfo		mIndexBufferInfo;

		union DrawParam
		{
			DrawIndexBufferParam	idx;
			DrawVertexBufferParam	vertex;
		};

		DrawParam	mDrawParam;
	};
}