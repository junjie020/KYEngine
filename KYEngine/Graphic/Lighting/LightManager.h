#pragma once
#include "Common/Singleton.h"
namespace KY
{
	class LightHWData
	{
	public:

	};

	template<class HWType>
	class TLight
	{
	public:
		void Update();
	private:
		HWType *mInternal;
	};

	using Light = TLight<LightHWData>;

	class LightManager : public Singleton<LightManager>
	{
	public:
		LightManager() = default;
		~LightManager() = default;

		void AddLight(const Light &l);

		void Update();

	private:
		using LightArray = std::vector<Light>;
		LightArray mLights;
	};
}
