////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SampleTest.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Graphic/Graphic.h"
#include "Graphic/Viewport.h"

#include "Graphic/Resource/ResourceManager.h"

#include "Common/CommonUtils.h"
#include "Scene/Model/Assimp/AssimpResourceManager.h"

namespace KY
{

	System::System()
		: mScene(nullptr)
		, mDimension(0, 0)
		, mWindowedMode(true)
		, mMainVP(nullptr)
	{
	}

	System::~System()
	{
		std::for_each(std::begin(mSamples), std::end(mSamples), SafeDelete<SampleTest>);
		mSamples.clear();

		SafeDelete(mScene);

		BOOST_ASSERT(!Graphic::HasInst());
		BOOST_ASSERT(!Input::HasInst());
	}


	bool System::Initialize(Size2U &dim, bool windowed)
	{
		mWindowedMode = windowed;
		InitializeWindows(dim, windowed);

		
		GraphicInitParam param = { dim.x, dim.y, 1, 0, FL_11_1, mhWnd, mWindowedMode };

		auto input = Input::Create();
		input->Initialize();

		auto graphic = Graphic::Create();

		mMainVP = graphic->CreateViewport(RectI(0, 0, dim.x, dim.y), Range2F(0, 1.0f));

		//{@
		Camera *camera = mMainVP->GetCamera();
		camera->SetPosition(Vec4f(0.0f, 0.0f, 100.f, 1.0f));
		camera->SetDirection(Vec4f(0.0f, 0.0f, 1.0f, 0.0f));
		
		//@}

		mScene = new Scene;

		AssimpResourceManager::Create();

		ResourceManager::Create();

		// Initialize the graphics object.		
		return Graphic::Inst()->Initialize(param);
	}


	void System::Shutdown()
	{
		// Release the graphics object.
		
		if (mMainVP)
		{
			Graphic::Inst()->DestoryViewport(mMainVP);
			mMainVP = nullptr;
		}

		Graphic::Inst()->Shutdown();

		Graphic::Destroy();
		Input::Destroy();
		
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

			if (Input::Inst()->IsKeyPressed(VK_ESCAPE) || msg.message == WM_QUIT)
				break;

			Frame();
		}

		return;
	}


	bool System::Frame()
	{
		mScene->Update(mMainVP);		
		mScene->Render(mMainVP);
		
		return Graphic::Inst()->CommitRenderCommands();
	}


	LRESULT CALLBACK System::MessageHandler(HWND hwnd, uint32 msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
		{
			
			Input::Inst()->KeyDown((uint32)wparam);
			return 0UL;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			Input::Inst()->KeyUp((uint32)wparam);
			return 0UL;
		}

		case WM_LBUTTONDOWN:
		{
			if (Input::Inst()->MouseButtonDown(MouseButtonType::Left))
			{
				return 0UL;
			}

			break;
		}
		// Any other messages send to the default message handler as our application won't make use of them.
		default:
			break;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
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
			if (0 == dim.x)
				dim.x = 800;
			if (0 == dim.y)
				dim.y = 600;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - dim.x) >> 1;
			posY = (GetSystemMetrics(SM_CYSCREEN) - dim.y) >> 1;
		}
		else
		{
			dim.x = uint32(GetSystemMetrics(SM_CXSCREEN));
			dim.y = uint32(GetSystemMetrics(SM_CYSCREEN));

			// If full screen set the screen to maximum size of the users desktop and 32bit.
			DEVMODE dmScreenSettings = { 0 };
			dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth	= dim.x;
			dmScreenSettings.dmPelsHeight	= dim.y;
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
			posX, posY, dim.x, dim.y, NULL, NULL, mhinstance, NULL);

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

	void System::AddSample(SampleTest *)
	{
		//auto result = std::find(std::begin(mSamples), std::end(mSamples), test);
		//if (result != std::end(mSamples))
		//	return;

		//test->Init();
		//mSamples.push_back(test);
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