#include "stdafx.h"
#include "Mesh.h"

#include "Graphic/Render/RenderOperation.h"
#include "Graphic/Camera/Camera.h"

#include "Graphic/Resource/ResourceManager.h"
#include "Graphic/Resource/Buffer/ConstBufferDef.h"
#include "Graphic/Resource/Shader/ShaderResourceView.h"
#include "Graphic/Render/RenderTarget.h"

#include "DebugUtils/TraceUtils.h"
#include "Math/VectorUnit.h"
#include "Platform/Win32DefHeader.h"

#include "Common/FileSystem/FileSystem.h"

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

	MeshRenderOperationHelper::MeshRenderOperationHelper() : mGlobalDynamicConstBuffer(ResourceType::Const)
		, mGlobalStaticConstBuffer(ResourceType::Const)
		, mMaterialConstBuffer(ResourceType::Const)
		, mLightElemBuffer(ResourceType::Shader)
		, mVS(nullptr)
		, mPS(nullptr)
		, mLightElemBufferResView(nullptr)
	{

	}

	MeshRenderOperationHelper::~MeshRenderOperationHelper()
	{

		for (auto vb : mVBs)
		{
			delete vb;
		}
		mVBs.clear();

		delete mLightElemBufferResView;
		mLightElemBufferResView = nullptr;
		mVS = nullptr;
		mPS = nullptr;
	}

	bool MeshRenderOperationHelper::Init(RenderTarget *rt)
	{
		if (!mVBs.empty())
		{
			if (!InitConstBuffer(rt))
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
		mRO.SetShader(mVS, ShaderType::ShdrT_Vertex);

		BOOST_ASSERT(mPS == nullptr);
		mPS = ResourceManager::Inst()->FindAddShader("Object.ps");
		mRO.SetShader(mPS, ShaderType::ShdrT_Pixel);
		//@}

		mVS->AddConstBuffer(0, &mGlobalDynamicConstBuffer);
		
		mPS->AddConstBuffer(0, &mGlobalDynamicConstBuffer);
		mPS->AddConstBuffer(1, &mGlobalStaticConstBuffer);
		mPS->AddConstBuffer(2, &mMaterialConstBuffer);		
		

		//{@	should move to lighting manager
		BOOST_ASSERT(nullptr == mLightElemBufferResView);
		mLightElemBufferResView = new ShaderResourceView;

		SRVParam srv;
		srv.type = SRVParam::SRVType::BufferEx;
		srv.fmt = TF_UNKNOWN;

		srv.bufferEx.firstElem = 0;
		srv.bufferEx.flags = 0;
		srv.bufferEx.numElems = 1;	// one directional light

		BOOST_VERIFY(mLightElemBufferResView->Init(srv, &mLightElemBuffer));

		mRO.SetPSShaderResourceView(8, mLightElemBufferResView);
		//@}

		
		return true;
	}

	bool MeshRenderOperationHelper::InitStates()
	{
		// should follow the mesh settings, hard code here
		return mStates.InitPipelineStateObj(&mRO);	//use default states
	}

	bool MeshRenderOperationHelper::InitConstBuffer(RenderTarget *rt)
	{
		mGlobalDynamicConstBuffer.Init({ ResourceType::Const, ResourceCPUAccess::Write, ResourceUsage::Dynamic, sizeof(GlobalDynamicConstBuffer) }, {nullptr, 0, 0});

		{
			GlobalStaticConstBuffer info;
			
			info.lightNum = 1;

			BufferParam param;
			param.type = ResourceType::Const;
			param.access = ResourceCPUAccess::None;
			param.usage = ResourceUsage::Default;
			param.sizeInBytes = sizeof(GlobalStaticConstBuffer);

			param.miscFlags = ResourceMiscFlag::Default;
			ResourceData resData;
			resData.pData = reinterpret_cast<const uint8*>(&info);
			resData.pitch = resData.slicePitch = 0;
			mGlobalStaticConstBuffer.Init(param, resData);
		}

		{
			// we need a lighting manager, this code must be move out here
			static_assert(sizeof(LightElemConstBuffer) == 64, "single light buffer should equal to 64 bytes, see Lighting.inc shader file, Light struct is 64 bytes");

			std::vector<LightElemConstBuffer>	lightsBuffer;

			lightsBuffer.push_back(LightElemConstBuffer());
			auto &lb = lightsBuffer.back();

			auto camera = rt->GetCamera();

			const auto &viewMat = camera->GetViewMat();

			const glm::vec4 lightPosInWS(10000.f, 10000.f, 10000.f, 1.0f);
			lb.positionInVS = viewMat * lightPosInWS;
			lb.directionInVS = glm::normalize(-lightPosInWS);

			lb.lightType = LightType::Directional;
			lb.angle = 360;
			lb.color = ColorF(0.2f, 0.2f, 0.2f, 1.0f);
			lb.range = -1.f;
			lb.intensity = 1.f;

			BufferParam param;
			param.type = ResourceType::Shader;
			param.access = ResourceCPUAccess::Write;
			param.usage = ResourceUsage::Dynamic;

			param.sizeInBytes = sizeof(LightElemConstBuffer) * lightsBuffer.size();

			param.byteStrideForStructureBuffer = sizeof(LightElemConstBuffer);
			param.miscFlags = ResourceMiscFlag::BufferStructured;
			ResourceData subData;
			subData.pData = reinterpret_cast<const uint8*>(&*lightsBuffer.begin());
			subData.pitch = 0,
			subData.slicePitch = 0;
			mLightElemBuffer.Init(param, subData);
		}

		{
			StaticMaterialConstBuffer buffer;
			buffer.diffColor		= ColorF(1.0f, 0, 0, 1.0f);
			buffer.specularColor	= ColorF(1.f, 1.f, 1.f, 1.f);
			buffer.emissiveColor	= ColorF::Black;
			buffer.ambientColor		= ColorF(0.02f, 0.02f, 0.02f, 1.0f);

			buffer.specularPow = 8.f;
			mMaterialConstBuffer.Init({ ResourceType::Const, ResourceCPUAccess::None, ResourceUsage::Immutable, sizeof(StaticMaterialConstBuffer) }, { reinterpret_cast<const uint8*>(&buffer), 0, 0 });
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

		if (!mIP.Init(*mVS))
		{
			DebugOutline("create mesh input layout failed!");
			return false;
		}

		mRO.SetInputLayout(&mIP);

		return true;

	}

	void MeshRenderOperationHelper::UpdateFrameData(Camera *camera)
	{
		ResourceMapParam param = { 0, ResourceMapType::ResMT_WriteDiscard, 0, 0, 0, false };
		if (mGlobalDynamicConstBuffer.Map(param))
		{
			BOOST_ASSERT(param.mapData.data);
			BOOST_ASSERT(param.mapData.rowPitch != 0);
			BOOST_ASSERT(param.mapData.rowPitch >= sizeof(GlobalDynamicConstBuffer));

			GlobalDynamicConstBuffer bb;
			bb.matrix.world = mat4x4_utils::INDENTIFY;
			
			bb.matrix.view = camera->GetViewMat();
			bb.matrix.proj = camera->GetProjMat();

			bb.eyePos = camera->GetPostion();

			memcpy(param.mapData.data, &bb, sizeof(bb));
			mGlobalDynamicConstBuffer.UnMap(param.subRes);
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

	bool Mesh::Init(RenderTarget *rt)
	{
		return mRenderHelper.Init(rt);
	}

	void Mesh::Update(Camera *camera)
	{

		mRenderHelper.UpdateFrameData(camera);
	}

	void Mesh::SetMeshPrimitiveType(PrimitiveType type)
	{
		mRenderHelper.SetMeshPrimitiveType(type);
	}

}