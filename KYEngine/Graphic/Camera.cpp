#include "stdafx.h"

#include "Camera.h"

namespace KY
{
	Camera::Camera(float fov, float aspect, float n, float f)
		: mOrtho(false)
		, mDirty(true)
	{
		mMatProj = std::move(ConstructPrespectiveMatrix(fov, aspect, n, f));

		UpdateRelatedMatrix();
	}

	Camera::Camera(bool ortho, float w, float h, float n, float f)
		: mMatProj(ConstructOrthoMatrix(w, h, n, f))
		, mOrtho(true)
	{
		BOOST_ASSERT(mOrtho == ortho);
	}

	void Camera::SetPosition(const Vec4f & pos)
	{
		SpaceNode::SetPosition(pos);
		mDirty = true;
	}

	void Camera::SetDirection(const Vec4f &dir)
	{
		SpaceNode::SetDirection(dir);
		mDirty = true;
	}

	void Camera::SetScale(const Vec4f &scale)
	{
		SpaceNode::SetScale(scale);
		mDirty = true;
	}

	void Camera::UpdateRelatedMatrix() const
	{
		if (!mDirty)
			return;

		const auto pos = GetPostion();
		mMatView = KY::ConstructViewMatrix(pos + GetDirection(), pos, Vec4f::YAXIS);
		mMatViewProj = mMatView * mMatProj;

		mFrustum.Update(mMatViewProj);
		
		mDirty = false;
	}

}
