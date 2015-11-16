#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Graphic/SpaceNode.h"
#include "Graphic/Frustum.h"

namespace KY
{
	class Camera : public SpaceNode
	{
	public:
		
	private:
		Frustum mFrustum;
	};
}
#endif	//__CAMERA_H__
