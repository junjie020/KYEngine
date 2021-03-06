#pragma once
#ifndef __IRENDERABLE_H__
#define __IRENDERABLE_H__

namespace KY
{
	class RenderCommandQueue;
	class IRenderable
	{
	public:
		//virtual void Render() = 0;

		virtual void ExtractRenderInfo(RenderCommandQueue &ro) = 0;
	};
}

#endif	//__IRENDERABLE_H__