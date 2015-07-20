#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Math/Rectangle.h"
#include "Math/Vector2.h"

namespace KY
{
    struct Viewport
    {
		Viewport() : mRect(0, 0, 1, 1), mDepthRange(0, 1.f){}

		~Viewport(){}

		RectU	mRect;
		Range2F mDepthRange;
    };
}
#endif // _VIEWPORT_H_