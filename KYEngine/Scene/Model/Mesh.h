#ifndef _MESH_H_
#define _MESH_H_

#include "Graphic/RenderOperation.h"
#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/Resource/IndexBuffer.h"
#include "Graphic/Resource/Shader.h"

#include "Graphic/Resource/StateHelper.h"
#include "Graphic/Resource/Buffer.h"

namespace KY
{
	class Camera;

	class MeshRenderOperationHelper
	{
	public:
		MeshRenderOperationHelper()
			: mDynConstBuffer(ResT_Const)
			, mLightConstBuffer(ResT_Const)
			, mVS(nullptr)
			, mPS(nullptr)
		{}

		~MeshRenderOperationHelper(){	
			for (auto vb : mVBs) {
				delete vb;
			}
		}
		RenderOperation& GetRO(){ return mRO; }

		typedef std::vector<VertexBuffer*> VertexBufferVec;
		VertexBufferVec& GetVBs() { return mVBs; }
		IndexBuffer& GetIB() { return mIB; }

		

		bool Init();
		
		void Update(Camera *camera);

		void SetMeshPrimitiveType(PrimitiveType type);
	private:
		bool InitShader();
		bool InitInputLayout();
		bool InitStates();
		bool InitConstBuffer();
	private:
		VertexBufferVec	mVBs;
		IndexBuffer		mIB;

		InputLayout		mIP;
		Shader*			mVS;
		Shader*			mPS;

		//{@	those const buffer should manager from a pool by camera or other data
		struct TransformConstData {

		};
		Buffer			mDynConstBuffer;
		Buffer			mLightConstBuffer;
		//@}


		StateHelper		mStates;

		RenderOperation mRO;
	};

    class Mesh
    {
    public:
		Mesh(): mNeedUpdate(true){}
		~Mesh(){}

		MeshRenderOperationHelper& GetRenderHelper() { return mRenderHelper; }

		bool Init();

		void Update(Camera *camera);
		void NeedUpdate() { mNeedUpdate = true; }

		void SetMeshPrimitiveType(PrimitiveType type);

    protected:
    	

    private:
		MeshRenderOperationHelper mRenderHelper;
		bool	mNeedUpdate;
    };
}
#endif // _MESH_H_