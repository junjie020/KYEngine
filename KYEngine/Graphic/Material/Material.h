#pragma once


namespace KY
{
	class Shader;
	class Texture;
	class SamplerStateObj;
	class RasterizerStateObj;
	class BlendStateObj;
	class DepthStencilStateObj;
	struct SamplerState;
	struct RasterizerState;
	struct DepthStencilState;
	struct BlendState;

	class Material
	{
	public:
		Material(const std::string &name) : mName(name){}
		const std::string GetName() const{
			return mName;
		}

		//{@
		void SetRasterizerStateObj(const RasterizerState &state);
		void SetBlendStateObj(const BlendState &state);
		void SetDepthStencilStateObj(const BlendState &state);

		RasterizerStateObj		*GetRasterizerStateObj() const {
			return mRasterizerStateObj;
		}

		BlendStateObj			*GetmBlendStateObj() const {
			return mBlendStateObj;
		}	

		DepthStencilStateObj	*GetDepthStencialStateObj() const {
			return mDepthStencialStateObj;
		}
		//@}

		void AddTexture(const fs::path &texPath, const SamplerState &state);
		void AddTexture(Texture *tex, SamplerStateObj *sampler);

		void SetShader(const fs::path &shaderFile);

	private:
		std::string mName;
		Shader *mShader;

		struct TextureData
		{
			Texture			*tex;
			SamplerStateObj *sampler;
		};

		using TextureArray = std::vector<TextureData>;
		TextureArray			mTextures;

		RasterizerStateObj		*mRasterizerStateObj;
		BlendStateObj			*mBlendStateObj;
		DepthStencilStateObj	*mDepthStencialStateObj;
	};
}
