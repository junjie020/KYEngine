#include "stdafx.h"

#include "Actor.h"
#include "Scene.h"
#include "Graphic/Camera.h"
#include "Graphic/RenderTarget.h"
#include "Graphic/RenderCommandQueue.h"
#include "Graphic/RenderOperation.h"

namespace KY
{
	Scene::Scene()
		: mRoot(new Actor(nullptr))		
	{

	}

	Scene::~Scene()
	{
		SafeDelete(mRoot);		
	}

	void Scene::Update(RenderTarget *rt)
	{
		mRoot->Update(rt->GetCamera(), mVisableActors);
	}

	void Scene::AddActor(Actor *act)
	{
		mRoot->AddChild(act);
	}

	void Scene::RemoveActor(Actor *act)
	{
		mRoot->RemoveChild(act);
	}

	void Scene::Render(RenderTarget *rt)
	{
		RenderCommandQueue queue;
		for (auto actor : mVisableActors)
		{
			RenderCommandQueue localQ;
			actor->ExtractRenderInfo(localQ);

			queue.Push(std::move(localQ));
		}

		rt->AddRenderQueue(std::move(queue));
	}
}