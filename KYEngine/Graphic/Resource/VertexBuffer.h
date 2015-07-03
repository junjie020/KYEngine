#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include "Resource.h"
#include "Graphic/DX/Buffer/DX11Buffer.h"
#include "Graphic/GraphicDef.h"

namespace KY
{
    class VertexBuffer : public Resource
    {
    public:    	
		VertexBuffer();
		~VertexBuffer();

		bool Create(const BufferParam &param, const ResourceData &resData);

    protected:
		DX::DX11Buffer	*mBuffer;
    };
}
#endif // _VERTEXBUFFER_H_