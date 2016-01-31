#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Graphic/SpaceNode.h"
#include "Graphic/IRenderable.h"
namespace KY
{
	class Camera;
	class Actor;
	using VisableActorVec = std::vector<Actor*>;

    class Actor : public SpaceNode
				, public IRenderable
    {
    public:
		Actor(Actor *pParent) 
			: mParent(pParent)
			, mVisable(false)
		{}
		virtual ~Actor(){}

		virtual void Update(Camera *camera, VisableActorVec &visableActors);

		virtual void UpdateImpl(Camera *){
			// todo, set always visable
			mVisable = true;
		}

		virtual void ExtractRenderInfo(RenderCommandQueue &/*q*/) override {}

		bool IsRoot() const {
			return nullptr != mParent;
		}

		bool IsVisable() const {
			return mVisable;
		}

		bool HasChild(Actor *rhs) const {
			return std::find(std::begin(mChildren), std::end(mChildren), rhs) != std::end(mChildren);
		}

		bool AddChild(Actor *rhs) {
			if (!HasChild(rhs)){
				rhs->mParent = this;
				mChildren.push_back(rhs);
				return true;
			}

			return false;
		}

		void RemoveChild(Actor *rhs){
			auto result = std::find(std::begin(mChildren), std::end(mChildren), rhs);
			if (std::end(mChildren) == result)
				return;

			mChildren.erase(result);
		}

    protected:
    	

    private:
		Actor *mParent;
		typedef std::vector<Actor*> ActorVec;

		ActorVec mChildren;

		bool mVisable : 1;
    };
}
#endif // _ACTOR_H_