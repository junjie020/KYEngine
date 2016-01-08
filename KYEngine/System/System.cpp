////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SampleTest.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Graphic/Graphic.h"
#include "Common/CommonUtils.h"
#include "Scene/Model/Assimp/AssimpResourceManager.h"

namespace KY
{

	System::System()
		: mInput(nullptr)
		, mGraphics(nullptr)
		, mScene(nullptr)
		, mDimension(0, 0)
		, mWindowedMode(true)
	{
	}

	System::~System()
	{
		std::for_each(std::begin(mSamples), std::end(mSamples), SafeDelete<SampleTest>);
		mSamples.clear();
	}


	bool System::Initialize(Size2U &dim, bool windowed)
	{
		mWindowedMode = windowed;
		InitializeWindows(dim, windowed);

		GraphicInitParam param = { dim.w, dim.h, 1, 0, FL_11_1, mhWnd, mWindowedMode };
		
		mInput = new Input;
		mInput->Initialize();

		mScene = new Scene;

		mGraphics = new Graphic;

		AssimpResourceManager::Create();

		// Initialize the graphics object.		
		return mGraphics->Initialize(param);
	}


	void System::Shutdown()
	{
		// Release the graphics object.
		if (mGraphics)
		{
			mGraphics->Shutdown();
			delete mGraphics;
			mGraphics = 0;
		}

		SafeDelete(mInput);
		SafeDelete(mScene);

		ShutdownWindows();
		return;
	}


	void System::Run()
	{
		MSG msg = { 0 };

		while (true)
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (mInput->IsKeyDown(VK_ESCAPE) || msg.message == WM_QUIT)
				break;

			Frame();
		}

		return;
	}


	bool System::Frame()
	{
		mScene->Update();
		mScene->Render();
		return mGraphics->Frame();
	}


	LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch (umsg)
		{
			// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			mInput->KeyDown((unsigned int)wparam);
			return 0;
		}

			// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			mInput->KeyUp((unsigned int)wparam);
			return 0;
		}

			// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
		}
	}


	void System::InitializeWindows(Size2U &dim, bool windowed)
	{
		WNDCLASSEX wc;		
		int posX, posY;

		// Get the instance of this application.
		mhinstance = GetModuleHandle(NULL);

		// Give the application a name.
		mApplicationName = L"KYEngine";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = mhinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = mApplicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
		if (windowed)
		{
			// If windowed then set it to 800x600 resolution.
			if (0 == dim.w)
				dim.w = 800;
			if (0 == dim.h)
				dim.h = 600;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - dim.w) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - dim.h) / 2;
		}
		else
		{
			dim.w = uint32(GetSystemMetrics(SM_CXSCREEN));
			dim.h = uint32(GetSystemMetrics(SM_CYSCREEN));

			// If full screen set the screen to maximum size of the users desktop and 32bit.
			DEVMODE dmScreenSettings = { 0 };
			dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth	= dim.w;
			dmScreenSettings.dmPelsHeight	= dim.h;
			dmScreenSettings.dmBitsPerPel	= 32;
			dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Change the display settings to full screen.
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			// Set the position of the window to the top left corner.
			posX = posY = 0;


		}

		// Create the window with the screen settings and get the handle to it.
		mhWnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, dim.w, dim.h, NULL, NULL, mhinstance, NULL);

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(mhWnd, SW_SHOW);
		SetForegroundWindow(mhWnd);
		SetFocus(mhWnd);

		// Hide the mouse cursor.
		if (!mWindowedMode)
			ShowCursor(false);

		return;
	}


	void System::ShutdownWindows()
	{
		// Show the mouse cursor.
		ShowCursor(true);

		// Fix the display settings if leaving full screen mode.
		if (!mWindowedMode)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		// Remove the window.
		DestroyWindow(mhWnd);
		mhWnd = NULL;

		// Remove the application instance.
		UnregisterClass(mApplicationName, mhinstance);
		mhinstance = NULL;

		return;
	}

	void System::Update()
	{

	}

	void System::AddSample(SampleTest *test)
	{
		auto result = std::find(std::begin(mSamples), std::end(mSamples), test);
		if (result != std::end(mSamples))
			return;

		test->Init();
		mSamples.push_back(test);
	}

	void System::RemoveSample(SampleTest *test)
	{
		auto result = std::find(std::begin(mSamples), std::end(mSamples), test);
		if (result != std::end(mSamples))
			mSamples.erase(result);
	}


	//static
	LRESULT CALLBACK System::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch (umessage)
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
			return System::Inst()->MessageHandler(hwnd, umessage, wparam, lparam);
		}
		}
	}
}