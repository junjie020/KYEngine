#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include "Resource.h"

namespace KY
{
    class VertexBuffer : public Resource
    {
    public:    	
		VertexBuffer();
		~VertexBuffer();

    protected:
    	

    private:
		uint32 mSizeInBytes;
    };
}
#endif // _VERTEXBUFFER_H_