////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	
	bool result;
	
	
	// Create the system object.
	KY::System* system = new KY::System;
	if(!system)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = system->Initialize();
	if(result)
	{
		system->Run();
	}

	// Shutdown and release the system object.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}