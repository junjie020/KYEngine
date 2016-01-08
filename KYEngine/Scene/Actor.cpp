#include "stdafx.h"
#include "Actor.h"
namespace KY
{
	void Actor::Update(Camera *camera, VisableActorVec &visableActors)
	{
		UpdateImpl(camera);
		if (IsVisable())
			visableActors.push_back(this);

		std::for_each(std::begin(mChildren), std::end(mChildren),
			[&](Actor *child) {
			child->Update(camera, visableActors);
		});
	}

}