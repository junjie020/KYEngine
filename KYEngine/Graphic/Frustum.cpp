#include "stdafx.h"
#include "Frustum.h"
#include "Math/MathUtils.h"
#include "Math/Plane.h"
#include "Math/VectorUnit.h"
namespace KY
{
	//static
	void Frustum::ExtractPlanes(const Mat4x4F &mat, PlaneArray &planes)
	{
		/**
		projMat =	{	col0 col1 col2 col3

						m00, m01, m02, m03,	// row0
						m10, m11, m12, m13,	// row1
						m20, m21, m22, m23,	// row2
						m30, m31, m32, m33,	// row3
						};
		vView = {x, y, z, w};

		P.S. ==> here '*' for dot

		then :
		vClip	= vView * projMat = {vView * col0, vView * col1, vView * col2, vView * col3};
				= {xC, yC, zC, wC};

		then :

		-wC < xC < wC
		-wC < yC < wC
		0	< zC < wC


		for left plane :
		-wC < xC	==> -(vView * col3) < vView * col0 ==> 0 < vView * col3 + vView * col0 ==> 0 < vView * (col0 + col3)
					==> 0 < vView * ({m00 + m03, m10 + m13, m20 + m23, m30 + m33})
					==> (m00 + m03)x + (m10 + m13)y + z(m20 + m23) + w(m30 + m33) > 0

		because vView is in view coordinate space, so w must be 1
					==> (m00 + m03)x + (m10 + m13)y + z(m20 + m23) + (m30 + m33) > 0

		then we let vView in left plane, so:
					==> (m00 + m03)x + (m10 + m13)y + z(m20 + m23) + (m30 + m33) = 0
					==> Ax + By + Cz + D = 0

		right :
					==> (m00 - m03)x + (m10 - m13)y + z(m20 - m23) + (m30 - m33) = 0

		top : 
					==> (m01 + m03)x + (m11 + m13)y + z(m21 + m23) + (m31 + m33) = 0
		bottom : 
					==> (m01 - m03)x + (m11 - m13)y + z(m21 - m23) + (m31 - m33) = 0
		near :
					==> vView * col2 = x(m02) + y(m12) + z(m22) + m32 = 0
		far :
					==>(m02 - m03)x + (m12 - m13)y + z(m22 - m23) + (m32 - m33) = 0
		the plane expression is coming out, but we must notice that, this plane is in VIEW COORDINATE SPACE
		*/

		auto &pLeft = planes[Frustum::Left];
		pLeft.x = mat[0][0] + mat[0][3];
		pLeft.y = mat[1][0] + mat[1][3];
		pLeft.z = mat[2][0] + mat[2][3];
		pLeft.dist = mat[3][0] + mat[3][3];

		auto &pRight = planes[Frustum::Right];
		pRight.x = mat[0][0] - mat[0][3];
		pRight.y = mat[1][0] - mat[1][3];
		pRight.z = mat[2][0] - mat[2][3];
		pRight.dist = mat[3][0] - mat[3][3];


		auto &pTop = planes[Frustum::Top];
		pTop.x = mat[0][1] + mat[0][3];
		pTop.y = mat[1][1] + mat[1][3];
		pTop.z = mat[2][1] + mat[2][3];
		pTop.dist = mat[3][1] + mat[3][3];

		auto &pBottom = planes[Frustum::Bottom];
		pBottom.x = mat[0][1] - mat[0][3];
		pBottom.y = mat[1][1] - mat[1][3];
		pBottom.z = mat[2][1] - mat[2][3];
		pBottom.dist = mat[3][1] - mat[3][3];

		auto &pNear = planes[Frustum::Near];
		pNear.x = mat[0][2];
		pNear.y = mat[1][2];
		pNear.z = mat[2][2];
		pNear.dist = mat[3][2];

		auto &pFar = planes[Frustum::Far];
		pFar.x = mat[0][2] - mat[0][3];
		pFar.y = mat[1][2] - mat[1][3];
		pFar.z = mat[2][2] - mat[2][3];
		pFar.dist = mat[3][2] - mat[3][3];

		
	}

	Frustum::Frustum(const Mat4x4F &viewProj)
	{
		Update(viewProj);
	}



	void Frustum::Update(const Mat4x4F &viewProj)
	{
		ExtractPlanes(viewProj, mPlanes);

		mPts[FarTopLeft] = KY::ToVec4(mPlanes[Frustum::Left].interset(mPlanes[Frustum::Top], mPlanes[Frustum::Far]));
		mPts[FarTopRight] = KY::ToVec4(mPlanes[Frustum::Right].interset(mPlanes[Frustum::Top], mPlanes[Frustum::Far]));

		mPts[FarBottomLeft] = KY::ToVec4(mPlanes[Frustum::Left].interset(mPlanes[Frustum::Bottom], mPlanes[Frustum::Far]));
		mPts[FarBottomRight] = KY::ToVec4(mPlanes[Frustum::Right].interset(mPlanes[Frustum::Bottom], mPlanes[Frustum::Far]));

		mPts[NearTopLeft] = KY::ToVec4(mPlanes[Frustum::Left].interset(mPlanes[Frustum::Top], mPlanes[Frustum::Near]));
		mPts[NearTopRight] = KY::ToVec4(mPlanes[Frustum::Right].interset(mPlanes[Frustum::Top], mPlanes[Frustum::Near]));

		mPts[NearBottomLeft] = KY::ToVec4(mPlanes[Frustum::Left].interset(mPlanes[Frustum::Bottom], mPlanes[Frustum::Near]));
		mPts[NearBottomRight] = KY::ToVec4(mPlanes[Frustum::Right].interset(mPlanes[Frustum::Bottom], mPlanes[Frustum::Near]));
	}

}
