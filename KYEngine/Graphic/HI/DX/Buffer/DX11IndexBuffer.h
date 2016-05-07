#ifndef _DX11INDEXBUFFER_H_
#define _DX11INDEXBUFFER_H_

#include "Graphic/HI/DX/Buffer/DX11Buffer.h"

#include <d3d11.h>

namespace KY 
{
	namespace DX 
	{
		class DX11IndexBuffer : public DX11Buffer
		{
		public:
			DX11IndexBuffer();
			~DX11IndexBuffer();

		protected:	
		};
	}
}
#endif // _DX11INDEXBUFFER_H_