////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Graphic/Graphic.h"
#include "Common/CommonUtils.h"
namespace KY
{

	System::System()
		: m_pInput(nullptr)
		, m_pGraphics(nullptr)
		, m_pScene(nullptr)
	{
	}

	System::~System()
	{
		
	}


	bool System::Initialize()
	{
		int screenWidth = 0, screenHeight = 0;
		InitializeWindows(screenWidth, screenHeight);

		m_pInput = new Input;
		m_pInput->Initialize();

		m_pScene = new Scene;

		m_pGraphics = new Graphic;
		
		// Initialize the graphics object.
		GraphicInitParam param = { screenWidth, screenHeight, 11, 1, 0, m_hwnd };
		return m_pGraphics->Initialize(param);		
	}


	void System::Shutdown()
	{
		// Release the graphics object.
		if (m_pGraphics)
		{
			m_pGraphics->Shutdown();
			delete m_pGraphics;
			m_pGraphics = 0;
		}

		SafeDelete(m_pInput);
		SafeDelete(m_pScene);

		ShutdownWindows();
		return;
	}


	void System::Run()
	{
		MSG msg = { 0 };
		
		bool done = false;
		while (!done)
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (m_pInput->IsKeyDown(VK_ESCAPE))
			{
				done = true;
				continue;
			}

			done = (msg.message != WM_QUIT) ? !Frame() : true;
		}

		return;
	}


	bool System::Frame()
	{
		m_pScene->Update();
		return m_pGraphics->Frame();		
	}


	LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch (umsg)
		{
			// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_pInput->KeyDown((unsigned int)wparam);
			return 0;
		}

			// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_pInput->KeyUp((unsigned int)wparam);
			return 0;
		}

			// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
		}
	}


	void System::InitializeWindows(int& screenWidth, int& screenHeight)
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;


		// Get an external pointer to this object.	
		ApplicationHandle = this;

		// Get the instance of this application.
		m_hinstance = GetModuleHandle(NULL);

		// Give the application a name.
		m_applicationName = L"Engine";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Determine the resolution of the clients desktop screen.
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
		if (FULL_SCREEN)
		{
			// If full screen set the screen to maximum size of the users desktop and 32bit.
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Change the display settings to full screen.
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			// Set the position of the window to the top left corner.
			posX = posY = 0;
		}
		else
		{
			// If windowed then set it to 800x600 resolution.
			screenWidth = 800;
			screenHeight = 600;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		}

		// Create the window with the screen settings and get the handle to it.
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(m_hwnd, SW_SHOW);
		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);

		// Hide the mouse cursor.
		ShowCursor(false);

		return;
	}


	void System::ShutdownWindows()
	{
		// Show the mouse cursor.
		ShowCursor(true);

		// Fix the display settings if leaving full screen mode.
		if (FULL_SCREEN)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		// Remove the window.
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;

		// Remove the application instance.
		UnregisterClass(m_applicationName, m_hinstance);
		m_hinstance = NULL;

		// Release the pointer to this class.
		ApplicationHandle = NULL;

		return;
	}

	void System::Update()
	{

	}

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}