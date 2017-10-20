#pragma once

#include "Graphic/GraphicDef.h"
#include "Graphic/Resource/Buffer/Buffer.h"

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
	class ShaderResourceView;

	class Material
	{
	public:
		Material(const std::string &name) 
			: mName(name)
			, mVSShader(nullptr)
			, mPSShader(nullptr)
		{

		}

		const std::string GetName() const
		{
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

		void SetShader(const fs::path &shaderFile, ShaderType type);

		const Shader* GetVSShader() const {
			return mVSShader;
		}

		const Shader* GetPSShader() const {
			return mPSShader;
		}

		struct TextureSamplerData
		{
			Texture				*tex;
			SamplerStateObj		*samplerObj;
			ShaderResourceView	*srv;
		};


		using TextureSamplerDataArray = std::vector<TextureSamplerData>;
		const TextureSamplerDataArray& GetTextureSamplerDataArray() const {
			return mTextureSamplers;
		}
		
	private:
		std::string mName;
		Shader *mVSShader;
		Shader *mPSShader;

		
		TextureSamplerDataArray	mTextureSamplers;

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

		std::vector<Buffer*>									mConstBuffers;
	};
}
