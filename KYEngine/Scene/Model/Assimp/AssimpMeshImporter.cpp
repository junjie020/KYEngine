#include "stdafx.h"
#include "AssimpMeshImporter.h"
#include "AssimpResourceManager.h"

//{@	assimp lib
#include "assimp/scene.h"
//@}

namespace KY
{
	

	AssimpMeshImporter::AssimpMeshImporter(Mesh *m)
		: MeshImporter(m)
	{

	}

	AssimpMeshImporter::~AssimpMeshImporter()
	{

	}

	bool AssimpMeshImporter::Import(const fs::path &filename)
	{
		auto scene = AssimpResourceManager::Inst()->FindRes(filename);
		return false;
	}

}