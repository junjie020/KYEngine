#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include "Singleton.h"
namespace KY
{
    class FileSystem : public Singleton<FileSystem>
    {
    public:
		FileSystem(){}
		~FileSystem(){}

		void ReigstPath(const std::string &subPath, const fs::path &p){
			BOOST_ASSERT(fs::exists(p));
			mSysPaths[subPath] = p;
		}

		typedef std::list<fs::path>	FilePathList;

		FilePathList ListPaths(const fs::path &path);
		FilePathList ListPathsRecursive(const fs::path &path);

		fs::path FindFromSubPath(const std::string &name) const{
			auto result = mSysPaths.find(name);
			if (result != mSysPaths.end())
				return result->second;

			return fs::path();
		}

		const fs::path& RootPath() const{
			return mRootPath;
		}
		void SetRootPath(const fs::path &rootPath){
			mRootPath = rootPath;
		}

	private:
		fs::path mRootPath;

		typedef std::unordered_map<std::string, fs::path>	SysPathMap;
		SysPathMap	mSysPaths;

    };
}
#endif // _FILESYSTEM_H_