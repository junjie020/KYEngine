#ifndef _HARDWAREBUFFER_H_
#define _HARDWAREBUFFER_H_

#include "Graphic/GraphicDef.h"
#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		class DX11Buffer
		{
		public:
			DX11Buffer(const BufferParam &param, const ResourceData &resData);
			virtual ~DX11Buffer();

			BufferType GetType() const { return mParam.type; }
			ResourceUsage GetUsage()const { return mParam.usage; }

			ID3D11Buffer* GetInternal() const { return mBuffer; }
		protected:
			BufferParam		mParam;
			ID3D11Buffer *mBuffer;
		};
	}
}
#endif // _HARDWAREBUFFER_H_