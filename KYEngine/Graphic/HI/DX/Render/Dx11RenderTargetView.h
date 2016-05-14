#ifndef _DX11RENDERTARGETVIEW_H_
#define _DX11RENDERTARGETVIEW_H_

#include "Graphic/GraphicDef.h"
#include "Graphic/HI/DX/Dx11HardwareInterface.h"
#include <d3d11.h>
namespace KY
{
	class Resource;
	namespace DX
	{
		class Dx11RenderTargetView : public Dx11HardwareInterface<ID3D11RenderTargetView>
		{
		public:

			bool Init(const RTVParam& param, Resource *res);
		};
	}

}
#endif // _DX11RENDERTARGETVIEW_H_