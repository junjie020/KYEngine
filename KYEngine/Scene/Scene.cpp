#include "stdafx.h"

#include "Actor.h"
#include "Scene.h"
#include "Graphic/Camera/Camera.h"
#include "Graphic/Render/RenderTarget.h"
#include "Graphic/Render/RenderCommandQueue.h"
#include "Graphic/Render/RenderOperation.h"

namespace KY
{
	Scene::Scene()
		: mRoot(new Actor(nullptr))		
		, mDirty(true)
	{

	}

	Scene::~Scene()
	{
		SafeDelete(mRoot);		
	}

	void Scene::Update(RenderTarget *rt)
	{
		if (mDirty)
		{
			mVisableActors.clear();
			mRoot->Update(rt->GetCamera(), mVisableActors);
		}
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
		if (false)
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
		else
		{
			for (auto actor : mVisableActors)
			{

			}
		}
	}
}