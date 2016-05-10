#pragma once
namespace KY 
{
	enum class TextureType : uint8
	{
		TT_1D = 0,
		TT_2D,
		TT_3D,
		TT_Cube,
	};

	template<TextureType TType, class HITextureType>
	class TextureTypeTraits
	{
	public:
		typedef HITextureType InternaleType;
		TextureTypeTraits() : mTex(nullptr){ }
		~TextureTypeTraits();
		HITextureType* Create();
		void Destory();

		HITextureType* GetInternal() { return mTex; }

		static TextureType GetType() {
			return TType;
		}
	private:
		HITextureType *mTex;
	};
}