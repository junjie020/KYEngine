#pragma once

#include "Graphic/GraphicDef.h"
namespace KY
{
	class TextureAssertLoader
	{
	public:
		virtual ~TextureAssertLoader(){}

		virtual size_t Width() const = 0;
		virtual size_t Height() const = 0;
		virtual size_t Depth() const = 0;
		virtual size_t RowPitch() const = 0;

		virtual size_t MipMapNum() const = 0;

		virtual const uint8* GetData() const = 0;
		virtual TexFormat GetTexFormat() const = 0;

	public:
		size_t GetSizeInBytes() const;
	};

	class TextureMemoryLoader : public TextureAssertLoader
	{
	public:
		using RawBuffer = std::vector<uint8>;

		TextureMemoryLoader(size_t w, size_t h, size_t mm, TexFormat fmt, std::vector<uint8> &&rb)
			: mWidth(w)
			, mHeight(h)
			, mMipmap(mm)
			, mFmt(fmt)
			, mRawBuffer(std::move(rb))
		{

		}

		virtual size_t Width() const override {
			return mWidth;
		}
		virtual size_t Height() const override{
			return mHeight;
		}
		virtual size_t Depth() const override{
			return 0;
		}
		virtual size_t RowPitch() const override {
			return Width();
		}

		virtual size_t MipMapNum() const override {
			return mMipmap;
		}

		virtual const uint8* GetData() const override {
			return &(*mRawBuffer.begin());
		}

		virtual TexFormat GetTexFormat() const override {
			return mFmt;
		}

	private:
		size_t mWidth, mHeight, mMipmap;
		TexFormat mFmt;
		RawBuffer mRawBuffer;
	};

	class TextureFileLoader : public TextureAssertLoader
	{
	public:

	};
}