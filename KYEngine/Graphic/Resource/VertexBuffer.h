#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include "Resource.h"
#include "Graphic/Resource/Buffer.h"
#include "Graphic/GraphicDef.h"

namespace KY
{
	namespace DX
	{
		class DX11Buffer;		
	}


    class VertexBuffer : public Buffer
    {
    public:    	
		VertexBuffer() : Buffer(ResT_Vertex){}
		~VertexBuffer(){}
    };
}
#endif // _VERTEXBUFFER_H_