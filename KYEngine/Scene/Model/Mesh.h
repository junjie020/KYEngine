#ifndef _MESH_H_
#define _MESH_H_

#include "Graphic/RenderOperation.h"
#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/Resource/IndexBuffer.h"
#include "Graphic/Resource/Shader.h"

namespace KY
{
	class MeshRenderOperationHelper
	{
	public:
		MeshRenderOperationHelper(){}

		~MeshRenderOperationHelper(){	
			for (auto vb : mVBs) {
				delete vb;
			}
		}
		RenderOperation& GetRO(){ return mRO; }

		typedef std::vector<VertexBuffer*> VertexBufferVec;
		VertexBufferVec& GetVBs() { return mVBs; }
		IndexBuffer& GetIB() { return mIB; }

		void Update();

	private:
		VertexBufferVec	mVBs;
		IndexBuffer		mIB;

		InputLayout		mIP;
		Shader			mVS;
		Shader			mPS;

		RenderOperation mRO;		
	};

    class Mesh
    {
    public:
		Mesh(): mNeedUpdate(true){}
		~Mesh(){}

		MeshRenderOperationHelper& GetRenderHelper() { return mRenderHelper; }

		void Update();

		void NeedUpdate() { mNeedUpdate = true; }
    protected:
    	

    private:
		MeshRenderOperationHelper mRenderHelper;
		bool			mNeedUpdate;
    };
}
#endif // _MESH_H_