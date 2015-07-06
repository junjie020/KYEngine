#include "stdafx.h"

#include "Actor.h"
#include "Scene.h"

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

	void Scene::Update()
	{
		mRoot->Update();
	}

	void Scene::AddActor(Actor *act)
	{
		mRoot->AddChild(act);
	}

	void Scene::RemoveActor(Actor *act)
	{
		mRoot->RemoveChild(act);
	}

}