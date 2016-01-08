#include "stdafx.h"
#include "Model.h"
#include "Mesh.h"

#include "Graphic/Graphic.h"
#include "Scene/Model/Assimp/AssimpMeshImporter.h"

namespace KY
{
	Model::~Model()
	{
		std::for_each(mMeshes.begin(), mMeshes.end(), SafeDelete<Mesh>);
	}

	void Model::UpdateImpl(Camera * /*camera*/)
	{

	}

	void Model::Render()
	{
		for (auto &m : mMeshes)
		{
			KY::Graphic::Inst()->AddRenderOperation(&m->GetRenderHelper().GetRO());
		}
	}

	bool Model::InitFromFile(const fs::path &file)
	{
		AssimpMeshImporter assimpImporter(this);

		return assimpImporter.Import(file);
	}

}
