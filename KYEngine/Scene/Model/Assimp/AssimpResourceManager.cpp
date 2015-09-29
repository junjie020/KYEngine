#include "stdafx.h"

#include "Common/HashImpl.h"
#include "AssimpResourceManager.h"

#include "assimp/Importer.hpp"

namespace KY
{
	AssimpResourceManager::AssimpResourceManager()
	{

	}

	AssimpResourceManager::~AssimpResourceManager()
	{

	}

	aiScene* AssimpResourceManager::FindRes(const fs::path &resName)
	{
		auto itFound = mResMap.find(resName);
		if (itFound != mResMap.end())
			return itFound->second;

		return nullptr;
	}

}