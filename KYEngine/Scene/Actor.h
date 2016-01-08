#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Graphic/SpaceNode.h"
#include "Graphic/IRenderable.h"
namespace KY
{
    class Actor : public SpaceNode
				, public IRenderable
    {
    public:
		Actor(Actor *pParent) : mParent(pParent){}
		virtual ~Actor(){}

		virtual void Update(){
			UpdateImpl();
			std::for_each(std::begin(mChildren), std::end(mChildren), 
				[](Actor *child){
					child->Update();
			});
		}

		virtual void UpdateImpl(){}

		virtual void Render(){}

		bool IsRoot() const {
			return nullptr != mParent;
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
    };
}
#endif // _ACTOR_H_