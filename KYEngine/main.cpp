////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System/System.h"
#include "System/SampleTest.h"

#include "Scene/Actor.h"
#include "Scene/Scene.h"

#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/RenderOperation.h"
#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Color.inl"

using namespace KY;
class SimpleTriangleTest : public KY::SampleTest
{
public:
	SimpleTriangleTest(){

	}
	~SimpleTriangleTest(){}
	bool Init() override
	{
		struct VertexColor{
			Vec4f		v;
			Color32B	c;
		};

		VertexColor vc[] = {
			{ Vec4f(-0.5f, 0.0f, 0.0f, 1.0f), Color32B::Red },
			{ Vec4f(0.0f, 0.5f, 0.0f, 1.0f), Color32B::Green },
			{ Vec4f(5.0f, 0.0f, 0.0f, 1.0f), Color32B::Blue },
		};

		BufferParam param;
		param.access = BA_None;
		param.usage = RU_Immutable;
		param.elemInBytes = sizeof(VertexColor);
		param.sizeInBytes = sizeof(vc);

		ResourceData data = { reinterpret_cast<const uint8*>(vc), 0, 0 };

		if (!mBuffer.Create(param, data))
			return false;

		RenderOperation ro;
		
		auto scene = System::Inst()->GetScene();
		BOOST_ASSERT(nullptr == mActor);
		mActor = new TriangleActor(&ro);
		scene->AddActor(mActor);
	}

private:
	class TriangleActor : public KY::Actor
	{
	public:
		TriangleActor(KY::RenderOperation *op) 
			: Actor(nullptr)
		{

		}

		~TriangleActor(){}
	};

private:
	KY::Actor *mActor;
	KY::VertexBuffer mBuffer;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Create the system object.
	auto system = KY::System::Create();

	if (system->Initialize())
	{
		SimpleTriangleTest tt;
		tt.Init();
		system->Run();
	}
	system->Shutdown();

	KY::System::Destroy();

	return 0;
}