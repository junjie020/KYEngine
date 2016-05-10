#pragma once

#include "Graphic/GraphicDef.h"
namespace KY
{
	class TextureAssertLoader
	{
	public:
		virtual ~TextureAssertLoader(){}

		virtual uint32 Width() const = 0;
		virtual uint32 Height() const = 0;
		virtual uint32 Depth() const = 0;
		virtual uint32 RowPitchInElem() const = 0;		

		virtual uint32 MipMapNum() const = 0;

		virtual const uint8* GetData() const = 0;
		virtual TexFormat GetTexFormat() const = 0;

	public:
		uint32 GetSizeInBytes() const;
		uint32 RowPitchInBytes() const;
	};

	class TextureMemoryLoader : public TextureAssertLoader
	{
	public:
		using RawBuffer = std::vector<uint8>;

		TextureMemoryLoader(uint32 w, uint32 h, uint32 mm, TexFormat fmt, std::vector<uint8> &&rb)
			: mWidth(w)
			, mHeight(h)
			, mMipmap(mm)
			, mFmt(fmt)
			, mRawBuffer(std::move(rb))
		{

		}

		virtual uint32 Width() const override {
			return mWidth;
		}
		virtual uint32 Height() const override{
			return mHeight;
		}
		virtual uint32 Depth() const override{
			return 0;
		}
		virtual uint32 RowPitchInElem() const override {
			return Width();
		}

		virtual uint32 MipMapNum() const override {
			return mMipmap;
		}

		virtual const uint8* GetData() const override {
			return &(*mRawBuffer.begin());
		}

		virtual TexFormat GetTexFormat() const override {
			return mFmt;
		}

	private:
		uint32 mWidth, mHeight, mMipmap;
		TexFormat mFmt;
		RawBuffer mRawBuffer;
	};

	class TextureFileLoader : public TextureAssertLoader
	{
	public:

	};
}