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

	void Model::UpdateImpl(Camera * camera)
	{
		Actor::UpdateImpl(camera);
	}

	void Model::ExtractRenderInfo(RenderCommandQueue &queue)
	{
		for (auto &m : mMeshes)
		{
			queue.Push(&(m->GetRenderHelper().GetRO()));
		}
	}

	void Model::InitRenderData()
	{
		for (auto &m : mMeshes)
		{
			m->Init();
		}
	}

	bool Model::InitFromFile(const fs::path &file)
	{
		AssimpMeshImporter assimpImporter(this);

		if (assimpImporter.Import(file))
		{
			InitRenderData();
		}

		return false;
	}

}
