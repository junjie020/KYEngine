#ifndef _RENDERTARGETVIEW_H_
#define _RENDERTARGETVIEW_H_
#include "Graphic/GraphicDef.h"

namespace KY
{
	class Resource;
	namespace DX
	{
		class Dx11RenderTargetView;
	}

    class RenderTargetView
    {
    public:
		RenderTargetView() : mRTV(nullptr){}
		~RenderTargetView();
		bool Init(const RTVParam &param, Resource *res);

		auto GetInternal() const { return mRTV; }
		bool IsVaild() const { return nullptr != mRTV; }
    private:
		DX::Dx11RenderTargetView *mRTV;
    };
}
#endif // _RENDERTARGETVIEW_H_