#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

#include "Math/Vector4.h"
#include "Math/Matrix.h"
namespace KY
{
    class Frustum
    {
    public:
		Frustum(){}
		// costruct a frustum in world space
		Frustum(const Mat4x4F &viewProj);

    	~Frustum();




    private:
		Vec4f mPts;	// in world space
    };
}
#endif // _FRUSTUM_H_