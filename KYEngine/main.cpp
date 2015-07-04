////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System/System.h"
#include "System/SampleTest.h"

#include "Scene/Actor.h"


class SimpleTriangleTest : public KY::SampleTest
{
public:
	~SimpleTriangleTest(){}
	bool Init() override
	{
		return true;
	}

	void Update() override
	{

	}
private:

};

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