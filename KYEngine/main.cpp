////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System/System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Create the system object.

	std::unique_ptr<KY::System> system(new KY::System);
	if (system->Initialize())
	{
		system->Run();
	}
	system->Shutdown();
	return 0;
}