#pragma once

#include "Graphic/GraphicDef.h"

namespace KY
{
	class TextureFormatHelper
	{
	public:
		static size_t GetElemSize(TexFormat fmt)
		{
			auto it = mData.find(fmt);
			if (it != mData.end())
				return it->second.size;

			BOOST_ASSERT(false && "not support format");
			return size_t(-1);
		}

		static glm::uvec3 GetMipmapLevelSize(size_t mip, const glm::uvec3 &dim)
		{
			return glm::uvec3(dim.x << mip, dim.y << mip, dim.z << mip);			
		}

	private:
		struct Format
		{
			size_t size;
		};

		using FormatData = std::unordered_map<TexFormat, Format>;

		static FormatData mData;
	};
}