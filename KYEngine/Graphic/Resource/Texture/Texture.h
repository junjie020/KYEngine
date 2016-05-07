#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Graphic/Resource/Resource.h"

namespace KY
{

	class TextureAssertLoader
	{
	public:

	};
    class Texture : public Resource
    {
    public:
    	Texture();
    	~Texture();

		bool Init(TextureAssertLoader *loader);

	private:


    };
}
#endif // _TEXTURE_H_