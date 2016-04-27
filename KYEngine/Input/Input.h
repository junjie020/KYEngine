#ifndef _INPUT_H_
#define _INPUT_H_

#include "Math/Vector2.h"
#include "Common/Singleton.h"

namespace KY
{
	enum class MouseButtonType : uint8
	{
		Left = 0, Middle, Right, Count,
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

		bool MouseButtonDown(MouseButtonType type);
		bool MouseMove();
		bool MouseButtonUp(MouseButtonType type);

		bool IsKeyPressed(uint8 key) const {
			return mKeysPressedState[key];
		}
		bool IsMouseBtnPressed(MouseButtonType type) const {
			return mMouseBtnsPressedState[uint32(type)];
		}

		const Pos2I& GetBtnDownPoint() const {
			return mBtnDownPoint;
		}

		const Pos2I& GetBtnUpPoint() const {
			return mBtnUpPoint;
		}

	private:
		Pos2I mBtnDownPoint;
		Pos2I mBtnUpPoint;
		
		bool mKeysPressedState[256];
		bool mMouseBtnsPressedState[MouseButtonType::Count];
	};
}
#endif