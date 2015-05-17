////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: System
////////////////////////////////////////////////////////////////////////////////
namespace KY
{
	class Graphic;
	class Input;

	class System
	{
	public:
		System();
		System(const System& rhs);
		~System();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		bool Frame();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

	private:
		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;

		Input* m_Input;
		Graphic* m_Graphics;
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