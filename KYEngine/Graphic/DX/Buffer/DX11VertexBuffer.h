#ifndef _DX11VERTEXBUFFER_H_
#define _DX11VERTEXBUFFER_H_

#include "Graphic/DX/Buffer/DX11Buffer.h"
#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		class DX11VertexBuffer : public DX11Buffer
		{
		public:
			DX11VertexBuffer(const BufferParam &param, const ResourceData &resData);
			~DX11VertexBuffer();
		protected:
		};
	}
}
#endif // _DX11VERTEXBUFFER_H_