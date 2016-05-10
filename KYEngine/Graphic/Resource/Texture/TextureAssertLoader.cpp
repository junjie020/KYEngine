
#include "stdafx.h"
#include "TextureAssertLoader.h"

#include "Graphic/Resource/Texture/TextureFormatHelper.h"

namespace KY
{
	uint32 TextureAssertLoader::GetSizeInBytes() const
	{
		const glm::uvec3 dim(RowPitchInElem(), Height(), Depth());

		uint32 sizeInBytes = 0;
		uint32 elemSize =	TextureFormatHelper::GetElemSize(GetTexFormat());
		for (uint32 ii = 0; ii < MipMapNum(); ++ii)
		{
			const glm::uvec3 dimMip = TextureFormatHelper::GetMipmapLevelSize(ii, dim);
			sizeInBytes += elemSize * dimMip.x * dimMip.y * dimMip.z;
		}

		return sizeInBytes;
	}



	KY::uint32 TextureAssertLoader::RowPitchInBytes() const
	{
		return TextureFormatHelper::GetElemSize(GetTexFormat()) * RowPitchInElem();
	}

}
