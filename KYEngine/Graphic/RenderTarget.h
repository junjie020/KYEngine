#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include "Graphic/Camera.h"

#include "Graphic/RenderCommandQueue.h"
#include "Graphic/RenderOperation.h"

namespace KY
{
    class RenderTarget
    {
    public:
		RenderTarget() {}
		virtual ~RenderTarget() {}

		Camera *GetCamera() {
			return &mCamera;
		}

		const Camera* GetCamera() const {
			return &mCamera;
		}

		RenderCommandQueue& GetRenderQueue() {
			return mQueue;
		}

		void AddRenderOperation(const RenderOperation &ro){
			mQueue.Push(&ro);
		}

		void AddRenderQueue(const RenderCommandQueue &q) {
			mQueue.Push(q);
		}

    private:
		RenderCommandQueue	mQueue;
		Camera				mCamera;
    };
}
#endif // _RENDERTARGET_H_