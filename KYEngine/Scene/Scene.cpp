#include "stdafx.h"

#include "Actor.h"
#include "Scene.h"

#include "Graphic/Resource/VertexBuffer.h"

#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Color.inl"

namespace KY
{
	Scene::Scene()
		: mRoot(new Actor)
	{

	}

	Scene::~Scene()
	{
		SafeDelete(mRoot);
	}

	void Scene::Update()
	{
		mRoot->Update();
		//struct VertexColor{
		//	Vec4f		v;
		//	Color32B	c;
		//};

		//VertexColor vc[] = {
		//	{ Vec4f(-0.5f, 0.0f, 0.0f, 1.0f), Color32B::Red },
		//	{ Vec4f(0.0f, 0.5f, 0.0f, 1.0f), Color32B::Green },
		//	{ Vec4f(5.0f, 0.0f, 0.0f, 1.0f), Color32B::Blue },
		//};
		//
		//BufferParam param;
		//param.access = BA_Write;
		//param.usage = RU_Dynamic;
		//param.elemInBytes = sizeof(VertexColor);
		//param.sizeInBytes = sizeof(vc);

		//VertexBuffer buffer;

		//ResourceData data = { reinterpret_cast<const uint8*>(vc), 0, 0 };

		//buffer.Create(param, data);


	}

}