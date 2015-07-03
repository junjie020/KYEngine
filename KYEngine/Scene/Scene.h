#ifndef _SCENE_H_
#define _SCENE_H_

namespace KY
{
	class Actor;
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Update();
	private:
		Actor	*mRoot;
	};
}
#endif //_SCENE_H_