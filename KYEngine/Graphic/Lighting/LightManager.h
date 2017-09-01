#pragma once
#include "Common/Singleton.h"
#include "Graphic/Resource/Buffer/Buffer.h"
#include "Math/Color.h"

namespace KY
{
	class ShaderResourceView;
	class RenderTarget;

	enum class LightType : uint32 {
		Directional,
		Point,
		Spot,
		Unknown
	};

	struct LightConstBuffer
	{
		glm::vec4	positionInVS;	// point and spot light
		glm::vec4	directionInVS;	// spot light
		ColorF		color;
		float		intensity;
		float		angle;			// spot
		float		range;			// point and spot light
		LightType	lightType;
	};

	class Light
	{
	public:
		void Update();

		LightConstBuffer	mInfo;
	};

	class LightManager : public Singleton<LightManager>
	{
	public:
		LightManager();
		~LightManager();

		void AddLight(const Light &l);

		void Update(RenderTarget *rt);
	private:
		void UpdateLightsBuffers(RenderTarget *rt);
		//void UpdateLightGlobalBuffer(RenderTarget *rt);
	
	private:
		using LightArray = std::vector<Light>;
		LightArray	mLights;

		Buffer		mLightsConstBuffer;
		ShaderResourceView* mLightElemBufferResView;
		//@}
	};
}
