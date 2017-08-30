#ifndef _MESH_H_
#define _MESH_H_

#include "Graphic/Render/RenderOperation.h"
#include "Graphic/Resource/Buffer/VertexBuffer.h"
#include "Graphic/Resource/Buffer/IndexBuffer.h"
#include "Graphic/Resource/Shader/Shader.h"

#include "Graphic/Resource/State/StateHelper.h"
#include "Graphic/Resource/Buffer/Buffer.h"

namespace KY
{
	class Camera;
	class RenderTarget;
	class MeshRenderOperationHelper
	{
	public:
		MeshRenderOperationHelper()
			: mDynConstBuffer(ResourceType::Const)
			, mGlobalLightBuffer(ResourceType::Const)
			, mMaterialConstBuffer(ResourceType::Const)
			, mLightElemBuffer(ResourceType::Shader)
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

		bool Init(RenderTarget *rt);
		
		void UpdateFrameData(Camera *camera);

		void SetMeshPrimitiveType(PrimitiveType type);
	private:
		bool InitShader();
		bool InitInputLayout();
		bool InitStates();
		bool InitConstBuffer(RenderTarget *rt);
	private:
		VertexBufferVec	mVBs;
		IndexBuffer		mIB;

		InputLayout		mIP;
		Shader*			mVS;
		Shader*			mPS;

		//{@	those const buffer should manager from a pool by camera or other data		
		Buffer			mDynConstBuffer;	
		Buffer			mMaterialConstBuffer;
		Buffer			mGlobalLightBuffer;

		//{@
		Buffer			mLightElemBuffer;
		ShaderResourceView* mLightElemBufferResView;

			//SRVParam p = { TF_R8G8B8A8_UNORM, SRVParam::SRVType::Tex2D,{ 0, 1 } };
		//mSRV->Init(p, mTex2D);
		//@}

		//@}


		StateHelper		mStates;

		RenderOperation mRO;
	};

	class RenderTarget;

    class Mesh
    {
    public:
		Mesh(): mNeedUpdate(true){}
		~Mesh(){}

		MeshRenderOperationHelper& GetRenderHelper() { return mRenderHelper; }

		bool Init(RenderTarget *rt);

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