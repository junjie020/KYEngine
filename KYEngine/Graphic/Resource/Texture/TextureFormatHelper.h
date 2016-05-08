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

		static void Init();

	private:
		struct Format
		{
			Format(size_t s, uint8 n) : size(s), elemNum(n){}
			size_t size;
			uint8 elemNum;
		};

		using FormatData = std::unordered_map<TexFormat, Format>;

		static FormatData mData;
	};
}