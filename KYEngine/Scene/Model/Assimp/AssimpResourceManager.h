#ifndef _ASSIMPRESOURCEMANAGER_H_
#define _ASSIMPRESOURCEMANAGER_H_

#include "Common/Singleton.h"
#include "Common/HashImpl.h"

struct aiScene;
namespace KY
{
	class AssimpResourceManager : public Singleton<AssimpResourceManager>
	{
	public:
		AssimpResourceManager();
		~AssimpResourceManager();

		const aiScene* FindRes(const fs::path &resName);

	private:
		typedef std::unordered_map<fs::path, const aiScene*> ResourceMap;

		ResourceMap	mResMap;
	};
}
#endif //_ASSIMPRESOURCEMANAGER_H_