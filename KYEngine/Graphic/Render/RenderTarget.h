#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include "Graphic/Camera/Camera.h"

#include "Graphic/Render/RenderCommandQueue.h"
#include "Graphic/Render/RenderOperation.h"
#include "Graphic/Render/RenderBatch.h"

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

		void AddRenderBatch(const RenderBatch &rb)
		{
			mRenderBatchs.push_back(rb);
		}

		auto& GetRenderBatchs()
		{
			return mRenderBatchs;
		}

    private:
		RenderCommandQueue	mQueue;
		Camera				mCamera;

		std::vector<RenderBatch>	mRenderBatchs;
    };
}
#endif // _RENDERTARGET_H_