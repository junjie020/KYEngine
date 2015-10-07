#include "stdafx.h"

#include "AssimpResourceManager.h"

#include "assimp/Importer.hpp"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace KY
{
	AssimpResourceManager::AssimpResourceManager()
	{

	}

	AssimpResourceManager::~AssimpResourceManager()
	{

	}

	const aiScene* AssimpResourceManager::FindRes(const fs::path &resName)
	{
		auto itFound = mResMap.find(resName);
		if (itFound != mResMap.end())
			return itFound->second;

		auto scene = aiImportFile(resName.string().c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

		mResMap[resName] = scene;
		return scene;
	}

}