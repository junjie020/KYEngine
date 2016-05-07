#ifndef _WINDOWRENDERTARGET_H_
#define _WINDOWRENDERTARGET_H_

#include "Graphic/Render/RenderTarget.h"
#include "Math/Rectangle.h"

namespace KY
{
    class WindowRenderTarget : public RenderTarget
    {
    public:
		WindowRenderTarget(const RectI& rt) : mRenderRect(rt){}
    	
    private:
		RenderCommandQueue mQueue;
		RectI mRenderRect;
    };
}
#endif // _WINDOWRENDERTARGET_H_