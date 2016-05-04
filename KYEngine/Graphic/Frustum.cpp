#include "stdafx.h"
#include "Frustum.h"
#include "Math/MathUtils.h"
#include "Math/Plane.h"
#include "Math/VectorUnit.h"
namespace KY
{
	//static
	void Frustum::ExtractPlanes(const Mat4x4F &/*mat*/, PlaneArray &/*planes*/)
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
		pLeft.x = mat.m00 + mat.m03;
		pLeft.y = mat.m10 + mat.m13;
		pLeft.z = mat.m20 + mat.m23;
		pLeft.dist = mat.m30 + mat.m33;

		auto &pRight = planes[Frustum::Right];
		pRight.x = mat.m00 - mat.m03;
		pRight.y = mat.m10 - mat.m13;
		pRight.z = mat.m20 - mat.m23;
		pRight.dist = mat.m30 - mat.m33;


		auto &pTop = planes[Frustum::Top];
		pTop.x = mat.m01 + mat.m03;
		pTop.y = mat.m11 + mat.m13;
		pTop.z = mat.m21 + mat.m23;
		pTop.dist = mat.m31 + mat.m33;

		auto &pBottom = planes[Frustum::Bottom];
		pBottom.x = mat.m01 - mat.m03;
		pBottom.y = mat.m11 - mat.m13;
		pBottom.z = mat.m21 - mat.m23;
		pBottom.dist = mat.m31 - mat.m33;

		auto &pNear = planes[Frustum::Near];
		pNear.x = mat.m02;
		pNear.y = mat.m12;
		pNear.z = mat.m22;
		pNear.dist = mat.m32;

		auto &pFar = planes[Frustum::Far];
		pFar.x = mat.m02 - mat.m03;
		pFar.y = mat.m12 - mat.m13;
		pFar.z = mat.m22 - mat.m23;
		pFar.dist = mat.m32 - mat.m33;

		
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
