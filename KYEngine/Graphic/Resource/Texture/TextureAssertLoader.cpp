
#include "stdafx.h"
#include "TextureAssertLoader.h"

#include "Graphic/Resource/Texture/TextureFormatHelper.h"

namespace KY
{
	size_t TextureAssertLoader::GetSizeInBytes() const
	{
		const glm::uvec3 dim(RowPitch(), Height(), Depth());

		size_t sizeInBytes = 0;
		size_t elemSize =	TextureFormatHelper::GetElemSize(GetTexFormat());
		for (size_t ii = 0; ii < MipMapNum(); ++ii)
		{
			const glm::uvec3 dimMip = TextureFormatHelper::GetMipmapLevelSize(ii, dim);
			sizeInBytes += elemSize * dimMip.x * dimMip.y * dimMip.z;
		}

		return sizeInBytes;
	}



}
