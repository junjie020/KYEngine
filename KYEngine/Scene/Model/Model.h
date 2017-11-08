#ifndef _MODEL_H_
#define _MODEL_H_

#include "Scene/Actor.h"

namespace KY
{
	class Mesh;
	class RenderTarget;
	class Model : public Actor
	{
	public:
		typedef std::vector<Mesh*> MeshVec;

		Model(Actor *pParent) : Actor(pParent){}
		~Model();

		bool InitFromFile(RenderTarget *rt, const fs::path &file);

		MeshVec& GetMeshes() { return mMeshes;  }	

	public:
		virtual void UpdateImpl(Camera *camera) override;
		virtual void ExtractRenderInfo(RenderCommandQueue &ro) override;
		virtual void ExtractRenderInfo(RenderBatchVec &rbVec) override;

	private:
		void InitRenderData(RenderTarget *rt);

	private:
		MeshVec mMeshes;
	};
}
#endif	//_MODEL_H_