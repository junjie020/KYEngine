#include "stdafx.h"

#include "Actor.h"
#include "Scene.h"
#include "Graphic/Camera.h"

namespace KY
{
	Scene::Scene()
		: mRoot(new Actor(nullptr))
		, mCamera(new Camera)
	{

	}

	Scene::~Scene()
	{
		SafeDelete(mRoot);
		SafeDelete(mCamera);
	}

	void Scene::Update()
	{
		mRoot->Update(mCamera, mVisableActors);
	}

	void Scene::AddActor(Actor *act)
	{
		mRoot->AddChild(act);
	}

	void Scene::RemoveActor(Actor *act)
	{
		mRoot->RemoveChild(act);
	}

	void Scene::Render()
	{
		for (auto actor : mVisableActors)
		{
			actor->Render();
		}
	}

}