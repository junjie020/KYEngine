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
			const auto &matView = mCamera->GetViewMat();

			const auto angles = glm::eulerAngles(glm::quat_cast(mat4x4_utils::INDENTIFY));

			const auto matDelta = glm::yawPitchRoll(yaw, pitch, 0.f);

			const glm::mat4x4 matViewNew = matView * matDelta;

			const glm::mat4x4 matWorldNew = glm::inverse(matViewNew);

			mCamera->SetWorldMat(matWorldNew);
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

