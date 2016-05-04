////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Input.h"

//{@	for handle camera
#include "System/System.h"
#include "Graphic/Viewport.h"
#include "Graphic/Camera.h"
#include "Graphic/CameraController.h"
//@}

#include "Math/MathUtils.h"

#include "glm/gtx/euler_angles.hpp"


namespace KY
{


	Input::Input()
		: mBtnDownPoint(0, 0)
		, mBtnUpPoint(0, 0)
		, mCurrentMousePoint(0, 0)
	{
		//ZERO_MEMORY(mKeysPressedState);
		//ZERO_MEMORY(mMouseBtnsPressedState);
	}


	Input::Input(const Input& /*other*/)
	{
		
	}


	Input::~Input()
	{
	}


	void Input::Initialize()
	{
		ZERO_MEMORY(mKeysPressedState);	
		ZERO_MEMORY(mMouseBtnsPressedState);
	}

	static bool HandleCameraMove(const glm::vec3 &delta)
	{
		auto vp = System::Inst()->GetMainVP();
		auto camera = vp->GetCamera();

		CameraController ctrller(camera);

		const glm::vec3 pos = camera->GetPostion();

		ctrller.Move(pos + delta);

		return true;
	}


	void Input::KeyDown(uint32 key)
	{
		mKeysPressedState[key] = true;

		if (mMouseBtnsPressedState[uint8(MouseButtonType::Left)])
		{
			glm::vec3 delta(0.f, 0.f, 0.f);
			switch (key)
			{
			case 'w':
			case 'W':
				delta.z = 1;
				break;
			case 's':
			case 'S':
				delta.z = -1;
				break;

			case 'a':
			case 'A':
				delta.x = 1;
				break;
			case 'd':
			case 'D':
				delta.x = -1;
				break;
			case 'q':
			case 'Q':
				delta.y = 1;
				break;
			case 'e':
			case 'E':
				delta.y = -1;
				break;
			default:
				break;
			}

			HandleCameraMove(delta);		
		}
		
		return;
	}


	void Input::KeyUp(uint32 key)
	{
		mKeysPressedState[key] = false;
		return;
	}

	static bool HandleCameraRotate(const glm::vec2 &currentPt, const glm::vec2 &lastPt)
	{
		auto vp = System::Inst()->GetMainVP();
		auto camera = vp->GetCamera();

		CameraController ctrller(camera);
		const auto delta = currentPt - lastPt;
		ctrller.Rotate(delta);

		return true;
	}

	// return false for not handle, return ture for handled
	bool Input::MouseButtonDown(MouseButtonMask mask)
	{
		UpdateMouseBtnState(mask, true);
		if (QueryBit(uint8(mask), uint8(MouseButtonMask::Left)))
		{
			return true;
		}
		return false;
	}

	bool Input::MouseMove(MouseButtonMask type, const glm::ivec2 &mousePt)
	{
		const auto lastMousePoint = mCurrentMousePoint;
		mCurrentMousePoint = mousePt;

		if (IsMouseBtnDown(MouseButtonType::Left) || QueryBit(uint8(MouseButtonMask::Left), uint8(type)))
		{
			return HandleCameraRotate(mCurrentMousePoint, lastMousePoint);
		}

		return false;
	}

	bool Input::MouseButtonUp(MouseButtonMask type)
	{
		UpdateMouseBtnState(MouseButtonMask(type), false);

		return false;
	}

	void Input::UpdateMouseBtnState(MouseButtonMask mask, bool value)
	{
		if (QueryBit(uint8(MouseButtonMask::Left), uint8(mask)))
			mMouseBtnsPressedState[uint8(MouseButtonType::Left)] = value;

		if (QueryBit(uint8(MouseButtonMask::Middle), uint8(mask)))
			mMouseBtnsPressedState[uint8(MouseButtonType::Middle)] = value;

		if (QueryBit(uint8(MouseButtonMask::Right), uint8(mask)))
			mMouseBtnsPressedState[uint8(MouseButtonType::Right)] = value;
	}

}