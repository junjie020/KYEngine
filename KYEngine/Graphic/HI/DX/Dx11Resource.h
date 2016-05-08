#ifndef _DX11RESOURCE_H_
#define _DX11RESOURCE_H_

#include <d3d11.h>
namespace KY
{
    class Dx11Resource
    {
    public:
		virtual ID3D11Resource *GetDxResource() = 0;
    private:

    };
}
#endif // _DX11RESOURCE_H_
