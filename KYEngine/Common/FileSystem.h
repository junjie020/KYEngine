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

		const std::string& RootPath() const{
			return mRootPath;
		}
		void SetRootPath(const std::string &rootPath){
			mRootPath = rootPath;
		}

	private:
		std::string mRootPath;

    };
}
#endif // _FILESYSTEM_H_