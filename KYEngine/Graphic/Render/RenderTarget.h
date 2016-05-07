#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include "Graphic/Camera/Camera.h"

#include "Graphic/Render/RenderCommandQueue.h"
#include "Graphic/Render/RenderOperation.h"

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

		void AddRenderQueue(RenderCommandQueue &&q) {
			mQueue.Push(std::forward<RenderCommandQueue>(q));
		}

    private:
		RenderCommandQueue	mQueue;
		Camera				mCamera;
    };
}
#endif // _RENDERTARGET_H_