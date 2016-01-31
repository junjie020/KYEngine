#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Math/Rectangle.h"
#include "Math/Vector2.h"

#include "Graphic/RenderTarget.h"

namespace KY
{
    class Viewport : public RenderTarget
    {
	public:
		Viewport() 
			: mRect(0, 0, 1, 1)
			, mDepthRange(0, 1.f)
		{}
		Viewport(const RectI& rt, const Range2F &depthrange) : mRect(rt), mDepthRange(depthrange){}

		~Viewport(){}

		void SetViewRect(const RectI &view) {
			mRect = view;
		}

		const RectI& GetViewRect() const {
			return mRect;
		}

		void SetDepthRange(const Range2F &dR) {
			mDepthRange = dR;
		}

		const Range2F& GetDepthRange() const {
			return mDepthRange;
		}



	private:
		RectI	mRect;
		Range2F mDepthRange;
    };
}
#endif // _VIEWPORT_H_