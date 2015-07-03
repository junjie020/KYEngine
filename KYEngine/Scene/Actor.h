#ifndef _ACTOR_H_
#define _ACTOR_H_

namespace KY
{
    class Actor
    {
    public:
		virtual ~Actor(){}

		virtual void Update(){}
		virtual void Render(){}

    protected:
    	

    private:
		typedef std::vector<Actor*> ActorVec;

		ActorVec mChildren;
    };
}
#endif // _ACTOR_H_