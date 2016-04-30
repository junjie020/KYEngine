////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Input.h"

//{@	for handle camera
#include "System/System.h"
#include "Graphic/Viewport.h"
#include "Graphic/Camera.h"
//@}


namespace KY
{


	Input::Input()
		: mBtnDownPoint(0, 0)
		, mBtnUpPoint(0, 0)
	{
		ZERO_MEMORY(mKeysPressedState);
		ZERO_MEMORY(mMouseBtnsPressedState);
	}


	Input::Input(const Input& /*other*/)
	{
		
	}


	Input::~Input()
	{
	}


	void Input::Initialize()
	{
		for (auto &key : mKeysPressedState)
			key = false;
	}


	void Input::KeyDown(uint32 key)
	{
		mKeysPressedState[key] = true;
		return;
	}


	void Input::KeyUp(uint32 key)
	{
		mKeysPressedState[key] = false;
		return;
	}

	class CameraController
	{
	public:
		CameraController(Camera *c) : mCamera(c){}

		void Rotate();
	private:
		Camera* mCamera;
	};
	static bool HandleCameraMove()
	{
		auto vp = System::Inst()->GetMainVP();
		auto camera = vp->GetCamera();

		const auto camerPos = camera->GetPostion();

		return false;
	}

	// return false for not handle, return ture for handled
	bool Input::MouseButtonDown(MouseButtonType type)
	{
		BOOST_ASSERT(type < MouseButtonType::Count);
		mMouseBtnsPressedState[uint32(type)] = true;
		if (type == MouseButtonType::Left)
		{
			return true;
		}
		return false;
	}

	bool Input::MouseMove()
	{
		return HandleCameraMove();
	}

	bool Input::MouseButtonUp(MouseButtonType type)
	{
		BOOST_ASSERT(type < MouseButtonType::Count);
		mMouseBtnsPressedState[uint32(type)] = false;

		return false;
	}
}