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

		enum FrustumPlaneName : uint8
		{
			Left, Right,
			Top, Bottom,
			Near, Far,

			PlaneCount,
		};


    private:
	
		enum FrustumPointIndex : uint8
		{
			NearTopLeft, NearTopRight,
			NearBottomLeft, NearBottomRight,

			FarTopLeft, FarTopRight,
			FarBottomLeft, FarBottomRight,

			IndexCount,
		};

		using FrustumPts = std::array<Vec4f, FrustumPointIndex::IndexCount>;
		FrustumPts mPts; // in world space		
    };
}
#endif // _FRUSTUM_H_