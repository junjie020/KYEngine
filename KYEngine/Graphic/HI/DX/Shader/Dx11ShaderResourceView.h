#ifndef _DX11SHADERRESOURCEVIEW_H_
#define _DX11SHADERRESOURCEVIEW_H_


#include "Graphic/HI/DX/Dx11HardwareInterface.h"
#include "Graphic/GraphicDef.h"

#include <d3d11.h>

namespace KY
{
	class Resource;

    class Dx11ShaderResourceView : public Dx11HardwareInterface<ID3D11ShaderResourceView>
    {
    public:

		bool Init(const SRVParam &param, Resource *res);
		
    };

}
#endif // _DX11SHADERRESOURCEVIEW_H_
