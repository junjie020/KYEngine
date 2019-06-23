#include "stdafx.h"

#include "Camera.h"
#include "Math/VectorUnit.h"

#include "glm/gtc/matrix_transform.hpp"

namespace KY
{
	Camera::Camera(float fov, float aspect, float n, float f)
		: mOrtho(false)
		, mDirty(true)
		, mUpVector(vec4_utils::YAXIS)		
		, mMatProj(glm::perspectiveLH(fov, aspect, n, f))
	{		
		
	}

	Camera::Camera(bool , float w, float h, float n, float f)
		: mMatProj(glm::ortho(w, h, n, f))
		, mOrtho(true)
		, mDirty(true)
	{
		mWorldMat = mat4x4_utils::INDENTIFY;		
		//BOOST_ASSERT(mOrtho == ortho);
	}

	void Camera::ConstructAsOrtho(float w, float h, float n, float f)
	{
		mOrtho = true;
		mDirty = true;
		mMatProj = std::move(glm::ortho(w, h, n, f));
		
	}

	void Camera::ConstructAsPrespective(float fov, float aspect, float n, float f)
	{
		mOrtho = false;
		mDirty = true;
		mMatProj = std::move(glm::perspectiveLH(fov, aspect, n, f));
	}

	void Camera::SetPosition(const glm::vec4 & pos)
	{
		SpaceNode::SetPosition(pos);
		mDirty = true;
	}

	void Camera::SetDirection(const glm::vec4 &dir)
	{
		SpaceNode::SetDirection(dir);
		mDirty = true;
	}

	void Camera::SetScale(const glm::vec4 &scale)
	{
		SpaceNode::SetScale(scale);
		mDirty = true;
	}

	void Camera::SetWorldMat(const glm::mat4x4 &matWorld)
	{
		SpaceNode::SetWorldMat(matWorld);
		mDirty = true;		
	}

	void Camera::UpdateRelatedMatrix()
	{
		if (!mDirty)
			return;

		const auto eye = GetPostion();
		const auto center = eye + GetDirection();
		
		mMatView = glm::lookAtLH(KY::ToVec3(eye), KY::ToVec3(center), KY::ToVec3(mUpVector));
		mMatViewProj = mMatView * mMatProj;

		mFrustum.Update(mMatViewProj);
		
		mDirty = false;
	}

}
