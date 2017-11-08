#pragma once
#ifndef __IRENDERABLE_H__
#define __IRENDERABLE_H__

#include "Graphic/Render/RenderBatch.h"

namespace KY
{
	class RenderCommandQueue;
	class IRenderable
	{
	public:
		//virtual void Render() = 0;

		virtual void ExtractRenderInfo(RenderCommandQueue &ro) = 0;
		virtual void ExtractRenderInfo(RenderBatchVec &rbVec) {}
	};
}

#endif	//__IRENDERABLE_H__