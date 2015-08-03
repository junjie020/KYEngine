#ifndef _DX11STATEOBJECT_H_
#define _DX11STATEOBJECT_H_

#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		template<class DX11STATEOBJTYPE>
		class Dx11StateObj
		{
		public:
			Dx11StateObj() : mInternalObj(nullptr)
			{}

			~Dx11StateObj()
			{
				SafeRelease(mInternalObj);
			}

			DX11STATEOBJTYPE* GetInternal() { return mInternalObj; }


		protected:
			DX11STATEOBJTYPE *mInternalObj;
		};

		class RasterizerState;
		class Dx11RasterizerStateObj : public Dx11StateObj<ID3D11RasterizerState>
		{
		public:
			bool Create(const RasterizerState &state);
		
		};

		class BlendState;
		class Dx11BlendStateObj : public Dx11StateObj<ID3D11BlendState>
		{
		public:			
			bool Create(const BlendState &state);
		
		};

		class DepthStencilState;
		class Dx11DepthStencilStateObj : public Dx11StateObj<ID3D11DepthStencilState>
		{
		public:

			bool Create(const DepthStencilState &state);

		
		};
	}

}
#endif //_DX11STATEOBJECT_H_