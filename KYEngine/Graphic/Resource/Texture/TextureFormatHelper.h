#pragma once

#include "Graphic/GraphicDef.h"

namespace KY
{
	class TextureFormatHelper
	{
	public:
		static uint32 GetElemSize(TexFormat fmt)
		{
			auto it = mData.find(fmt);
			if (it != mData.end())
				return it->second.size;

			BOOST_ASSERT(false && "not support format");
			return uint32(-1);
		}

		static glm::uvec3 GetMipmapLevelSize(uint32 mip, const glm::uvec3 &dim)
		{
			return glm::uvec3(dim.x << mip, dim.y << mip, dim.z << mip);			
		}

		static void Init();

	private:
		struct Format
		{
			Format(uint32 s, uint8 n) : size(s), elemNum(n){}
			uint32 size;
			uint8 elemNum;
		};

		using FormatData = std::unordered_map<TexFormat, Format>;

		static FormatData mData;
	};
}