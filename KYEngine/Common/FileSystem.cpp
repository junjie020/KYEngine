#include "stdafx.h"
#include "FileSystem.h"
namespace KY
{
	

	FileSystem::FilePathList FileSystem::ListPaths(const fs::path &path)
	{
		FilePathList paths;
		for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it)
		{
			const auto &p = it->path();
			if (fs::is_regular_file(p))
			{
				paths.push_back(p);
				continue;
			}
		}

		return paths;
	}

	FileSystem::FilePathList FileSystem::ListPathsRecursive(const fs::path &path)
	{
		FilePathList paths;
		for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it)
		{
			const fs::path &curPath = it->path();
			if (fs::is_directory(curPath))
			{
				auto tmp = ListPathsRecursive(curPath);
				paths.insert(paths.end(), tmp.begin(), tmp.end());
				return paths;
			}

			if (fs::is_regular_file(curPath))
			{
				paths.push_back(*it);
				continue;
			}
		}

		return paths;
	}

	FileSystem::ReadFileResult FileSystem::ReadFileContent(const fs::path &fullFileName, std::string &fileContent) const
	{
		std::ifstream iftm(fullFileName.string().c_str());

		if (!iftm)
			return ReadFileResult::RFR_CouldNotFindTheFile;

		iftm.seekg(std::ios::end, 0);
		const auto fileSize = size_t(iftm.tellg());
		iftm.seekg(std::ios::beg, 0);

		fileContent.resize(fileSize);

		iftm.read(&*fileContent.begin(), fileSize);

		return ReadFileResult::RFR_Success;
	}

}