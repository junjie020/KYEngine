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

		}
		RenderOperation& GetRO(){ return mRO; }

		typedef std::vector<VertexBuffer> VertexBufferVec;
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
		Mesh(){}
		~Mesh(){}

		MeshRenderOperationHelper& GetRenderHelper() { return mRenderHelper; }

		void Update();
    protected:
    	

    private:
		MeshRenderOperationHelper mRenderHelper;
    };
}
#endif // _MESH_H_