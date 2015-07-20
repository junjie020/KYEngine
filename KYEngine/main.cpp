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
#include "Graphic/Graphic.h"

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
		auto scene = System::Inst()->GetScene();
		BOOST_ASSERT(nullptr == mActor);
		mActor = new TriangleActor;
		scene->AddActor(mActor);

		return true;
	}

private:
	class TriangleActor : public KY::Actor
	{
	public:
		TriangleActor() 
			: Actor(nullptr)
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

			if (mBuffer.Create(param, data))
			{
				RenderOperation::BufferInfo info = { 0, 3 };
				mRO.SetVertexBuffer(&mBuffer, info);				
			}
		}

		~TriangleActor(){}

		virtual void UpdateImpl()
		{
			KY::Graphic::Inst()->AddRenderOperation(&mRO);			
		}
	private:
		KY::RenderOperation mRO;
		KY::VertexBuffer mBuffer;
	};

private:	
	KY::Actor *mActor;
};

#include "Common/FileSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Create the system object.
	KY::FileSystem::Create();

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