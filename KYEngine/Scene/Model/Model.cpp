#include "stdafx.h"
#include "Model.h"
#include "Mesh.h"

namespace KY
{
	Model::~Model()
	{
		std::for_each(mMeshes.begin(), mMeshes.end(), SafeDelete<Mesh>);
	}

}