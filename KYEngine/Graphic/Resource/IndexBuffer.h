#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#include "Resource.h"

namespace KY
{
	namespace DX
	{
		class DX11Buffer;
	}

    class IndexBuffer : public Resource
    {
    public:
    	IndexBuffer();
    	~IndexBuffer();

    protected:
    	

    private:
		DX::DX11Buffer	*mBuffer;
    };
}
#endif // _INDEXBUFFER_H_