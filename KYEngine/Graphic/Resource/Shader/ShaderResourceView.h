#ifndef _SHADERRESOURCEVIEW_H_
#define _SHADERRESOURCEVIEW_H_

#include "Graphic/GraphicDef.h"
#include "Graphic/Resource/IResourceInterface.h"

#include "Graphic/HI/DX/Shader/Dx11ShaderResourceView.h"

namespace KY
{
	class Resource;
    class ShaderResourceView : public IResourceInterface<DX::Dx11ShaderResourceView>
    {
    public:
		bool Init(const SRVParam &param, Resource *res);
    };
}
#endif // _SHADERRESOURCEVIEW_H_