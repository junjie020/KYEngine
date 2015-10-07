#ifndef _MODEL_H_
#define _MODEL_H_

namespace KY
{
	class Mesh;
	class Model
	{
	public:
		typedef std::vector<Mesh*> MeshVec;

		Model(){}
		~Model();

		MeshVec& GetMeshes() { return mMeshes;  }

	private:
		MeshVec mMeshes;
	};
}
#endif	//_MODEL_H_