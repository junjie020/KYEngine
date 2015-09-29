#ifndef _ASSIMPRESOURCEMANAGER_H_
#define _ASSIMPRESOURCEMANAGER_H_

#include "Common/Singleton.h"

struct aiScene;
namespace KY
{
	class AssimpResourceManager : public Singleton<AssimpResourceManager>
	{
	public:
		AssimpResourceManager();
		~AssimpResourceManager();

		aiScene* FindRes(const fs::path &resName);

	private:
		typedef std::unordered_map<fs::path, aiScene*> ResourceMap;

		ResourceMap	mResMap;
	};
}
#endif //_ASSIMPRESOURCEMANAGER_H_