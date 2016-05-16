#ifndef _RENDERTARGETVIEW_H_
#define _RENDERTARGETVIEW_H_
#include "Graphic/GraphicDef.h"
#include "Graphic/Resource/IResourceInterface.h"

#include "Graphic/HI/DX/Render/Dx11RenderTargetView.h"

namespace KY
{
	class Resource;
    class RenderTargetView : public IResourceInterface<DX::Dx11RenderTargetView>
    {
    public:
		bool Init(const RTVParam &param, Resource *res);
    };
}
#endif // _RENDERTARGETVIEW_H_