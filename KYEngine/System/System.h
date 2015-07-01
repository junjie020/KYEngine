////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


////////////////////////////////////////////////////////////////////////////////
// Class name: System
////////////////////////////////////////////////////////////////////////////////
namespace KY
{
	class Graphic;
	class Input;
	class Scene;

	class System
	{
		System(const System& rhs);
	public:
		System();
		
		~System();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		bool Frame();
		void Update();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

	private:
		LPCWSTR		mApplicationName;
		HINSTANCE	mhinstance;
		HWND		mhWnd;

		Input*		mInput;
		Graphic*	mGraphics;
		Scene*		mScene;
	};
}

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static KY::System* ApplicationHandle = 0;


#endif