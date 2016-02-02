#include "stdafx.h"
#include "Mesh.h"

#include "Graphic/RenderOperation.h"
#include "Graphic/Camera.h"

#include "Graphic/Resource/ResourceManager.h"
#include "Graphic/Resource/ConstBufferDef.h"

#include "DebugUtils/TraceUtils.h"

#include "Platform/Win32DefHeader.h"

#include "Common/FileSystem.h"

namespace KY
{
	static auto get_semantic_name(const VertexBuffer *vb, const RenderOperation &ro)
	{
		const char* semanticNames[] = 
		{
			"POSITION",
			"NORMAL",
			"TANGENT",
			"BINORMAL",
			"BLENDWEIGHT",
			"BLENDINDICES",
			"COLOR",
			"COLOR1",
			"COLOR2",
			"COLOR3",

			"TEXCOORD",
			"TEXCOORD1",
			"TEXCOORD2",
			"TEXCOORD3",
		};

		const auto& vbis = ro.GetVertexBufferInfos();

		for (const auto& vbi : vbis)
		{
			if (vb == vbi.mVertexBuf)
			{
				uint32 semanticIdx = 0U;
			
				const uint32 slotIdx = std::min(vbi.mVertexInfo.slotIdx, COUNT_OF(semanticNames));
				if (SI_Color <= slotIdx && slotIdx < (SI_Color + MAX_SLOT_ELEM_IDX))
					semanticIdx = slotIdx - SI_Color;
				else if (SI_Texcoord <= slotIdx && slotIdx < (SI_Texcoord + MAX_SLOT_ELEM_IDX)) 
					semanticIdx = slotIdx - SI_Texcoord;

				return std::make_tuple(semanticNames[slotIdx], semanticIdx, SlotIndex(slotIdx));
			}
				
		}

		return std::make_tuple("", uint32(-1), SI_Unknown);
	}

	static auto get_tex_format(SlotIndex slotIdx)
	{
		switch (slotIdx)
		{
		case SI_Position:
			return TF_R32G32B32_FLOAT;
		case SI_Color:
			return TF_R8G8B8A8_UINT;
		case SI_Normal:
			return TF_R32G32B32_FLOAT;
		case SI_Texcoord:
			return TF_R32G32_FLOAT;

		default:
			return TF_FORCE_UINT;
		}
	}

	bool MeshRenderOperationHelper::Init()
	{
		if (!mVBs.empty())
		{
			if (!InitConstBuffer())
				return false;

			if (!InitShader())
				return false;

			if (!InitInputLayout())
				return false;

			if (!InitStates())
				return false;

			
		}

		return true;
	}

	bool MeshRenderOperationHelper::InitShader()
	{
		//{@	hard code here, we need to follow the mesh's properties to define which shader should use or which macro should define
		BOOST_ASSERT(mVS == nullptr);
		mVS = ResourceManager::Inst()->FindAddShader("Object.vs");
		mRO.SetShader(mVS, ShdrT_Vertex);

		BOOST_ASSERT(mPS == nullptr);
		mPS = ResourceManager::Inst()->FindAddShader("Object.ps");
		mRO.SetShader(mPS, ShdrT_Pixel);
		//@}

		mVS->AddConstBuffer(0, &mDynConstBuffer);
		//mVS->AddConstBuffer(1, &mLightConstBuffer);
		mPS->AddConstBuffer(0, &mDynConstBuffer);
		//mPS->AddConstBuffer(1, &mLightConstBuffer);



		
		return true;
	}

	bool MeshRenderOperationHelper::InitStates()
	{
		// should follow the mesh settings, hard code here
		return mStates.Init(&mRO);	//use default states
	}

	bool MeshRenderOperationHelper::InitConstBuffer()
	{
		mDynConstBuffer.Create({ ResT_Const, BA_Write, RU_Dynamic, sizeof(TransformConstBuffer) }, {nullptr, 0, 0});


		{
			StaticLightConstBuffer buffer;
			//Scene *scene = System::Inst()->GetScene();
			//LightSystem* lightSys = scene->GetLightSystem();

			//StaticLightInfo* staticLightInfo = lightSys->GetStaticInfo();

			mLightConstBuffer.Create({ ResT_Const, BA_None, RU_Immutable, sizeof(StaticLightConstBuffer) }, { reinterpret_cast<const uint8*>(&buffer), 0, 0 });
		}

		
		return true;
	}

	bool MeshRenderOperationHelper::InitInputLayout()
	{
		mIP.Clean();

		for (const VertexBuffer* vb : mVBs)
		{
			const auto semanticInfo = get_semantic_name(vb, mRO);
			const auto slotIdx = std::get<2>(semanticInfo);
			const InputElemDesc elem =
			{
				std::get<0>(semanticInfo),
				std::get<1>(semanticInfo),
				get_tex_format(slotIdx),
				slotIdx,
				0,	// struct arrays
				0,
				false,
			};

			mIP.AddElem(elem);
		}

		BOOST_ASSERT(mVS->IsValid());

		if (!mIP.Create(*mVS))
		{
			DebugOutline("create mesh input layout failed!");
			return false;
		}

		mRO.SetInputLayout(&mIP);

		return true;

	}

	void MeshRenderOperationHelper::Update(Camera *camera)
	{
		//camera->

		ResourceMapParam param = { 0, ResMT_WriteDiscard, 0, 0, 0, false };
		if (mDynConstBuffer.Map(param))
		{
			BOOST_ASSERT(param.mapData.data);
			BOOST_ASSERT(param.mapData.rowPitch != 0);
			BOOST_ASSERT(param.mapData.rowPitch >= sizeof(TransformConstBuffer));

			TransformConstBuffer bb;
			bb.matWorld = camera->GetViewMat();
			bb.matView = camera->GetViewMat();
			bb.matProj = camera->GetProjMat();

			param.mapData.data = reinterpret_cast<uint8*>(&bb);
			mDynConstBuffer.UnMap(param.subRes);
		}
		else
		{
			KY::DebugOutline("map const buffer failed!");
		}
	}

	void MeshRenderOperationHelper::SetMeshPrimitiveType(PrimitiveType type)
	{
		mRO.SetPrimitiveType(type);
	}

	bool Mesh::Init()
	{
		return mRenderHelper.Init();
	}

	void Mesh::Update(Camera *camera)
	{
		if (mNeedUpdate)
		{
			mRenderHelper.Update(camera);
			mNeedUpdate = false;
		}
			
	}

	void Mesh::SetMeshPrimitiveType(PrimitiveType type)
	{
		mRenderHelper.SetMeshPrimitiveType(type);
	}

}