////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


////////////////////////////////////////////////////////////////////////////////
// Class name: System
////////////////////////////////////////////////////////////////////////////////
#include "Common/Singleton.h"

namespace KY
{
	class Graphic;
	class Input;
	class Scene;

	class SampleTest;

	class System : public Singleton<System>
				 , public boost::noncopyable
	{
		System(const System& rhs);
	public:
		System();
		
		~System();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

		void AddSample(SampleTest *test);
		void RemoveSample(SampleTest *test);

		Scene* GetScene() { return mScene;  }

	private:
		bool Frame();
		void Update();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	private:
		LPCWSTR		mApplicationName;
		HINSTANCE	mhinstance;
		HWND		mhWnd;

		Input*		mInput;
		Graphic*	mGraphics;
		Scene*		mScene;

		typedef std::vector<SampleTest*>	SampleTestVec;
		SampleTestVec	mSamples;
	};
}

#endif