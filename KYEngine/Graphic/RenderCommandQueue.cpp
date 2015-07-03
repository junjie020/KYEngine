#include "stdafx.h"
#include "RenderCommandQueue.h"
namespace KY
{
	RenderCommandQueue::~RenderCommandQueue()
	{
		BOOST_ASSERT(mROList.empty());
	}

	void RenderCommandQueue::Push(const RenderOperation *ro)
	{
		mROList.push_back(ro);
	}

	const RenderOperation* RenderCommandQueue::Pop()
	{
		const RenderOperation *ro = mROList.front();
		mROList.pop_front();
		return ro;
	}

}