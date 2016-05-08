#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Graphic/Resource/Resource.h"

#include "Graphic/Resource/Texture/TextureTypeTraits.h"

namespace KY
{
	class Texture : public Resource
	{
	public:
		Texture()
			: Resource(ResT_Texture)
		{}

	};

	template<class TraitsType>
    class TextureImpl : public Texture
    {
    public:
    	~TextureImpl();

		bool Init(const TextureParam &param, class TextureAssertLoader *loader);

		typename TraitsType::InternaleType* GetInternal() {
			return mTex.GetInternal();
		}

	private:
		void Destory();

	private:
		TraitsType	mTex;

    };
}
#endif // _TEXTURE_H_