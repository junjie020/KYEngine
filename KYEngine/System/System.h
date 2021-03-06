////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


////////////////////////////////////////////////////////////////////////////////
// Class name: System
////////////////////////////////////////////////////////////////////////////////
#include "Common/Singleton.h"
#include "Math/Vector2.h"

namespace KY
{
	class Graphic;
	class Input;
	class Scene;
	class Viewport;

	class SampleTest;

	class System : public Singleton<System>
#if NEED_BOOST
		, public boost::noncopyable
#endif
	{
		System(const System& rhs);
	public:
		System();
		
		~System();

		bool Initialize(Size2U &dim, bool windowed);
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, uint32, WPARAM, LPARAM);

		void AddSample(SampleTest *test);
		void RemoveSample(SampleTest *test);

		Scene* GetScene() { return mScene;  }

		Viewport* GetMainVP() { return mMainVP;  }

	private:
		bool Frame();
		void Update();
		void InitializeWindows(Size2U &dim, bool windowed);
		void ShutdownWindows();

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	private:
		LPCWSTR		mApplicationName;
		HINSTANCE	mhinstance;
		HWND		mhWnd;

		Scene*		mScene;
		Viewport*	mMainVP;

		Size2U		mDimension;
		bool		mWindowedMode;

		typedef std::vector<SampleTest*>	SampleTestVec;
		SampleTestVec	mSamples;
	};
}

#endif