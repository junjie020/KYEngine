#ifndef _HARDWAREBUFFER_H_
#define _HARDWAREBUFFER_H_

#include "Graphic/GraphicDef.h"
#include "Graphic/HI/DX/Dx11HardwareInterface.h"
#include "Graphic/HI/DX/Dx11Resource.h"
#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		class DX11Buffer : public Dx11HardwareInterface<ID3D11Buffer>
						 //, public Dx11Resource
		{
		public:
			DX11Buffer(const BufferParam &param, const ResourceData &resData);			

			//virtual ID3D11Resource* GetDxResource() override {
			//	return GetInternal();
			//}

			bool Map(ResourceMapParam &param);
			void UnMap(uint32 subRes);

			const BufferParam& GetBufferParam() const { return mParam; }

			ResourceType GetType() const { return mParam.type; }
			ResourceUsage GetUsage()const { return mParam.usage; }

		protected:
			BufferParam		mParam;			
		};
	}
}
#endif // _HARDWAREBUFFER_H_