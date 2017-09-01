#pragma once

#include "Graphic/GraphicDef.h"
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

		void Update();
	public:
		//{@
		void SetRasterizerStateObj(const RasterizerState &state);
		void SetBlendStateObj(const BlendState &state);
		void SetDepthStencilStateObj(const BlendState &state);

		RasterizerStateObj		*GetRasterizerStateObj() const {
			return mRasterizerState.obj;
		}

		BlendStateObj			*GetmBlendStateObj() const {
			return mBlendState.obj;
		}	

		DepthStencilStateObj	*GetDepthStencialStateObj() const {
			return mDepthStencilState.obj;
		}
		//@}

		void AddTexture(const fs::path &texPath, const SamplerState &state);
		void AddTexture(Texture *tex, SamplerStateObj *sampler);

		void SetShader(const fs::path &shaderFile);


	private:
		

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

		template<typename StateType, class ObjType>
		class StateObj
		{
		public:
			StateObj();
			~StateObj();

			void SetDirty(bool d) {
				dirty = d;
			}
			bool IsDirty() const {
				return dirty;
			}

		public:
			StateType	state;
			ObjType*	obj;
			bool		dirty;
		};

		StateObj<RasterizerState, RasterizerStateObj>		mRasterizerState;
		StateObj<BlendState, BlendStateObj>					mBlendState;
		StateObj<DepthStencilState, DepthStencilStateObj>	mDepthStencilState;
	};
}
