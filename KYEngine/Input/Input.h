#ifndef _INPUT_H_
#define _INPUT_H_

#include "Math/Vector2.h"
#include "Common/Singleton.h"

namespace KY
{
	enum class MouseButtonMask : uint8
	{
		Left = 0x01,
		Middle = 0x02, 
		Right = 0x04, 		
	};

	enum class KeyboradKey : uint16
	{
		//KK_CAP
		//KK_A = 0,
		//KK_Z
	};

	class InputTranslatorWin32
	{
	public:
		//static 
	};

	class Input : public Singleton<Input>
	{
	public:
		Input();
		Input(const Input&);
		~Input();

		void Initialize();

		void KeyDown(uint32 key);
		void KeyUp(uint32 key);

		bool MouseButtonDown(MouseButtonMask type);
		bool MouseMove(MouseButtonMask type, const glm::ivec2 &mousePt);
		bool MouseButtonUp(MouseButtonMask type);

		bool IsKeyPressed(uint8 key) const {
			return mKeysPressedState[key];
		}
		bool IsMouseBtnPressed(MouseButtonMask type) const {
			return mMouseBtnsPressedState[uint32(type)];
		}

		const Pos2I& GetBtnDownPoint() const {
			return mBtnDownPoint;
		}

		const Pos2I& GetBtnUpPoint() const {
			return mBtnUpPoint;
		}

		enum class MouseButtonType : uint8
		{
			Left = 0, Middle, Right, Count,
		};

		bool IsMouseBtnDown(MouseButtonType type) const {
			return mMouseBtnsPressedState[uint8(type)];
		}

	private:
		void UpdateMouseBtnState(MouseButtonMask type, bool value);


	private:
		Pos2I mBtnDownPoint;
		Pos2I mBtnUpPoint;
		Pos2I mCurrentMousePoint;
		
	
		bool mKeysPressedState[256];

		bool mMouseBtnsPressedState[MouseButtonType::Count];
	};
}
#endif