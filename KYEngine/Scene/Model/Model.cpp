#include "stdafx.h"
#include "Model.h"
#include "Mesh.h"

#include "Graphic/Graphic.h"
#include "Graphic/Render/RenderCommandQueue.h"
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

		for (auto &m : mMeshes)
		{
			m->Update(camera);
		}
	}

	void Model::ExtractRenderInfo(RenderCommandQueue &queue)
	{
		for (auto &m : mMeshes)
		{
			queue.Push(&(m->GetRenderHelper().GetRO()));
		}
	}

	void Model::ExtractRenderInfo(RenderBatchVec &rbVec)
	{

	}

	void Model::InitRenderData(RenderTarget *rt)
{
		for (auto &m : mMeshes)
		{
			m->Init(rt);
		}
	}

	bool Model::InitFromFile(RenderTarget *rt, const fs::path &file)
	{
		AssimpMeshImporter assimpImporter(this);

		if (assimpImporter.Import(file))
		{
			InitRenderData(rt);
		}

		return false;
	}

}
