#include "stdafx.h"

#include "Graphic/Camera/CameraController.h"

#include "Graphic/Camera/Camera.h"

#include "Math/MathUtils.h"

#include "glm/gtx/euler_angles.hpp"

namespace KY
{
	CameraController::CameraController(Camera *c) : mCamera(c)
	{

	}

	void CameraController::Rotate(const glm::vec2 &delta)
	{
		BOOST_ASSERT(mCamera);

		const float yaw = glm::radians(-delta.x * msRotateSpeed);
		const float pitch = glm::radians(-delta.y * msRotateSpeed);

		if (!(MathUtils::IS_ZERO(yaw) && MathUtils::IS_ZERO(pitch)))
		{
			const auto matDelta = glm::yawPitchRoll(yaw, pitch, 0.f);

			const auto matWorld = mCamera->GetWorldMat();
			mCamera->SetWorldMat(matWorld * matDelta);
			//const glm::mat4x4 matWorldNew = glm::inverse(matViewNew);

			//mCamera->SetWorldMat(matWorldNew);

			//auto eye = mCamera->GetPostion();
			//auto center = eye + mCamera->GetDirection();

			//auto newEye = eye * matDelta;
			//auto newDir = center - eye;
			//mCamera->SetPosition(newEye);
			//mCamera->SetDirection(glm::normalize(newDir));

		}
	}

	void CameraController::Move(const glm::vec3 &delta)
	{
		mCamera->SetPosition(glm::vec4(delta, 1.0f));
	}

	void CameraController::SetRotateSpeed(float speed)
	{
		msRotateSpeed = speed;
	}

	void CameraController::SetMoveSpeed(float speed)
	{
		msMoveSpeed = speed;
	}

	//static 
	float CameraController::msRotateSpeed = 1.f;

	//static 
	float CameraController::msMoveSpeed = 1.f;
}

