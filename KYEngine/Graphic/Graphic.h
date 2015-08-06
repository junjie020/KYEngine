#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GraphicDef.h"
#include "Common/Singleton.h"
#include "Graphic/PipelineStage.h"
#include "Math/Vector2.h"
namespace KY
{
	namespace DX
	{
		class Dx11;
	}

	class RenderCommandQueue;
	class RenderOperation;

	class Graphic : public Singleton<Graphic>
	{
		Graphic(const Graphic&);
	public:
		Graphic();
		~Graphic();

		bool Initialize(const GraphicInitParam& param);
		void Shutdown();
		bool Frame();		

		void AddRenderOperation(RenderOperation *ro);

		PipelineStage* GetStage(StageType type, bool bInit = false);

		Size2U GetBackBufferSize() const { return Size2U(mInitParam.width, mInitParam.height); }

	public:
		//{@	internal
		DX::Dx11* GetDx11();
		FeatureLevel GetDXFeatureLevel() const;
		//@}

	private:
		bool Render();
		void CommitRenderData();

		template<class StageClass>
		StageClass* GetStage(bool bInit);

	private:
		GraphicInitParam	mInitParam;
		DX::Dx11			*mDx;
		RenderCommandQueue	*mQueue;

		//{@ stage
		union{
			PipelineStage* mStages[ST_Count];
			struct {
				IAStage* mIAStage;
				VSStage* mVSStage;
				HSStage* mHSStage;
				TSStage* mTessStage;
				DSStage* mDSStage;
				GSStage* mGSStage;
				SOStage* mSOStage;
				RSStage* mRSStage;
				PSStage* mPSStage;
				OMStage* mOMStage;
			};
		};
		//@}
		
	};

	inline DX::Dx11* Graphic::GetDx11(){
		return mDx;
	}
	inline FeatureLevel Graphic::GetDXFeatureLevel() const{
		return mInitParam.featureLevel;
	}

}
#endif
