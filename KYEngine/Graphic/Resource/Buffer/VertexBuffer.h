#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/Resource/Buffer/Buffer.h"
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
		VertexBuffer() : Buffer(ResourceType::Vertex){}
		~VertexBuffer(){}
    };
}
#endif // _VERTEXBUFFER_H_