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

	public:
		void ReplaceCamera(Camera *camera);

		// do not try to reference the camera pointer, just for temp use, like change the camera position
		Camera* GetCameraForTempUse() {
			return mCamera;
		}
	
	private:
		Actor	*mRoot;

		// maybe use the camera object not the pointer style is more safe. And not allow other object to reference the camera directly.
		Camera  *mCamera;

		using VisableActorVec = std::vector<Actor*>;
		VisableActorVec mVisableActors;
	};
}
#endif //_SCENE_H_