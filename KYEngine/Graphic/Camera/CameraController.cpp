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

			auto dir = mCamera->GetDirection();
			mCamera->SetDirection(dir * matDelta);
		}
	}

	void CameraController::Move(CameraMoveType type, const glm::vec3 &delta)
	{
		glm::vec4 newPos;

		switch (type)
		{
		case KY::CameraController::MT_Direction:
		{
			auto dir = mCamera->GetDirection();
			newPos = mCamera->GetPostion() + glm::normalize(dir) * msMoveSpeed * delta.z;
		}			
			break;
		case KY::CameraController::MT_LeftRight:
		{
			newPos = mCamera->GetPostion();
			newPos.x += delta.x * msMoveSpeed;
		}
			break;
		case KY::CameraController::MT_UpDown:
		{
			newPos = mCamera->GetPostion();
			newPos.y += delta.y * msMoveSpeed;
		}
			break;
		default:
			break;
		}

		mCamera->SetPosition(newPos);
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

