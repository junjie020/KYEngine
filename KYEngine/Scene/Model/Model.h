#ifndef _MODEL_H_
#define _MODEL_H_

#include "Scene/Actor.h"

namespace KY
{
	class Mesh;
	class Model : public Actor
	{
	public:
		typedef std::vector<Mesh*> MeshVec;

		Model(Actor *pParent) : Actor(pParent){}
		~Model();

		bool InitFromFile(const fs::path &file);

		MeshVec& GetMeshes() { return mMeshes;  }

		virtual void UpdateImpl() override;
	private:
		MeshVec mMeshes;
	};
}
#endif	//_MODEL_H_