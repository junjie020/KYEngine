#ifndef _SCENE_H_
#define _SCENE_H_

namespace KY
{
	class Actor;
	class Camera;

	class RenderTarget;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void Update(RenderTarget *rt);
		void AddActor(Actor *act);
		void RemoveActor(Actor *act);
		void Render(RenderTarget *rt);
		Actor* GetRootActor() { return mRoot; }	
	
	private:
		Actor	*mRoot;

		using VisableActorVec = std::vector<Actor*>;
		VisableActorVec mVisableActors;

		bool mDirty;
	};
}
#endif //_SCENE_H_