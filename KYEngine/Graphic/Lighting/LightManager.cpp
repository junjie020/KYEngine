#include "stdafx.h"
#include "LightManager.h"
#include "Graphic/Render/RenderTarget.h"
#include "Graphic/Resource/Shader/ShaderResourceView.h"

#include "DebugUtils/TraceUtils.h"

namespace KY
{
	//////////////////////////////////////////////////////////////////////////
	void Light::Update()
	{

	}

	//////////////////////////////////////////////////////////////////////////

	LightManager::LightManager()
		: mLightsConstBuffer(ResourceType::Shader)
		, mLightElemBufferResView(nullptr)
	{

	}

	LightManager::~LightManager()
	{
		SafeDelete(mLightElemBufferResView);
	}

	void LightManager::AddLight(const Light &l)
	{
		mLights.push_back(l);
	}

	void LightManager::Update(RenderTarget *rt)
	{
		UpdateLightsBuffers(rt);

	}

	//inline constexpr bool AlignShaderBuffer(Type )

	void LightManager::UpdateLightsBuffers(RenderTarget *rt)
	{
		rt;

		std::vector<LightConstBuffer>	buffers;

		for (auto &l : mLights)
		{
			l.Update();
			buffers.push_back(l.mInfo);
		}

		// we need a lighting manager, this code must be move out here
		static_assert(sizeof(LightConstBuffer) == 64, "single light buffer should equal to 64 bytes, see Lighting.inc shader file, Light struct is 64 bytes");

		//auto camera = rt->GetCamera();

		//const auto &viewMat = camera->GetViewMat();

		//const glm::vec4 lightPosInWS(10000.f, 10000.f, 10000.f, 1.0f);
		//lb.positionInVS = viewMat * lightPosInWS;
		//lb.directionInVS = glm::normalize(-lightPosInWS);

		//lb.lightType = LightType::Directional;
		//lb.angle = 360;
		//lb.color = ColorF(0.2f, 0.2f, 0.2f, 1.0f);
		//lb.range = -1.f;
		//lb.intensity = 1.f;

		BufferParam param;
		param.type = ResourceType::Shader;
		param.access = ResourceCPUAccess::Write;
		param.usage = ResourceUsage::Dynamic;

		param.sizeInBytes = (uint32_t)(sizeof(LightConstBuffer) * buffers.size());

		param.byteStrideForStructureBuffer = sizeof(LightConstBuffer);
		param.miscFlags = ResourceMiscFlag::BufferStructured;
		ResourceData subData;
		subData.pData = reinterpret_cast<const uint8*>(&*buffers.begin());
		subData.pitch = 0,
		subData.slicePitch = 0;
		if (mLightsConstBuffer.Init(param, subData))
		{
			DebugOutline("create light const buffer failed!");
			return;
		}

		SafeDelete(mLightElemBufferResView);
		if (mLightElemBufferResView == nullptr)
			mLightElemBufferResView = new ShaderResourceView;

		SRVParam srv;
		srv.type = SRVParam::SRVType::BufferEx;
		srv.fmt = TF_UNKNOWN;

		srv.bufferEx.firstElem	= 0;
		srv.bufferEx.flags		= 0;
		srv.bufferEx.numElems	= (uint32_t)buffers.size();	// one directional light

		BOOST_VERIFY(mLightElemBufferResView->Init(srv, &mLightsConstBuffer));

	}

	//void LightManager::UpdateLightGlobalBuffer(RenderTarget *rt)
	//{
	//	GlobalStaticConstBuffer info;

	//	info.lightNum = 1;

	//	BufferParam param;
	//	param.type = ResourceType::Const;
	//	param.access = ResourceCPUAccess::None;
	//	param.usage = ResourceUsage::Default;
	//	param.sizeInBytes = sizeof(GlobalStaticConstBuffer);

	//	param.miscFlags = ResourceMiscFlag::Default;
	//	ResourceData resData;
	//	resData.pData = reinterpret_cast<const uint8*>(&info);
	//	resData.pitch = resData.slicePitch = 0;
	//	mGlobalStaticConstBuffer.Init(param, resData);
	//	
	//}

}