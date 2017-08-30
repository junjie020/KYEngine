#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#include "Graphic/Resource/Buffer/Buffer.h"
namespace KY
{
	namespace DX
	{
		class DX11Buffer;
	}

    class IndexBuffer : public Buffer
    {
    public:
		IndexBuffer() : Buffer(ResourceType::Index){}
		~IndexBuffer(){}
    };
}
#endif // _INDEXBUFFER_H_