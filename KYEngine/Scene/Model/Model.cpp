#include "stdafx.h"
#include "Model.h"
#include "Mesh.h"

#include "Graphic/Graphic.h"
#include "Graphic/RenderCommandQueue.h"
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

	void Model::ExtractRenderInfo(RenderCommandQueue &queue)
	{
		for (auto &m : mMeshes)
		{
			queue.Push(&(m->GetRenderHelper().GetRO()));
		}
	}

	bool Model::InitFromFile(const fs::path &file)
	{
		AssimpMeshImporter assimpImporter(this);

		return assimpImporter.Import(file);
	}

}
