#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GraphicDef.h"
#include "Common/Singleton.h"
#include "Graphic/PipelineStage.h"
namespace KY
{


	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

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

		DX::Dx11* GetDx11();

		void AddRenderOperation(RenderOperation *ro);

		PipelineStage* GetStage(StageType type, bool bInit = false);

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
}
#endif
