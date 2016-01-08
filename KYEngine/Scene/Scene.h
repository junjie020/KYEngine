#ifndef _SCENE_H_
#define _SCENE_H_

namespace KY
{
	class Actor;
	class Camera;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void Update();
		void AddActor(Actor *act);
		void RemoveActor(Actor *act);
		void Render();
		Actor* GetRootActor() { return mRoot; }

		void SetCamera(Camera *camera) {
			mCamera = camera;
		}

	private:
		Actor	*mRoot;
		Camera  *mCamera;

		using VisableActorVec = std::vector<Actor*>;
		VisableActorVec mVisableActors;
	};
}
#endif //_SCENE_H_