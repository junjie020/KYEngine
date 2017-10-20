#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GraphicDef.h"
#include "Common/Singleton.h"
#include "Graphic/Stage/PipelineStage.h"
#include "Math/Vector2.h"
#include "Math/Rectangle.h"
#include "Graphic/Render/RenderBatch.h"

namespace KY
{
	namespace DX
	{
		class Dx11;
	}

	class RenderCommandQueue;
	class RenderOperation;

	class RenderTarget;
	class WindowRenderTarget;
	class Viewport;
	class GlobalConstBuffer;

	class Graphic : public Singleton<Graphic>
	{
		Graphic(const Graphic&);
	public:
		Graphic();
		~Graphic();

		bool Initialize(const GraphicInitParam& param);
		void Shutdown();		

		PipelineStage* GetStage(StageType type, bool bInit = false);
		Size2U GetBackBufferSize() const { return Size2U(mInitParam.width, mInitParam.height); }

		Viewport* CreateViewport(const RectI &rt, const Range2F &r);
		void DestoryViewport(Viewport *vp);

		WindowRenderTarget* CreateWindowRenderTarget(const RectI &rt);
		void DestoryRenderTarget(WindowRenderTarget *rt);
		//RenderTexture* CreateRenderTexture();


		bool CommitRenderCommands();

		GlobalConstBuffer* GetGlobalConstBuffer() const {
			return mGlobalConstBuffer;
		}

		void AddRenderBatch(const RenderBatch &batch);
		void AddRenderBatch(const RenderBatch &batch, RenderTarget *rt);
		
	public:
		//{@	internal
		DX::Dx11* GetDx11();
		FeatureLevel GetDXFeatureLevel() const;
		//@}

	private:
		
		void CommitRenderData();
		void CommitRenderBatch();

		template<class StageClass>
		StageClass* GetStage(bool bInit);

	private:
		GraphicInitParam	mInitParam;
		DX::Dx11			*mDx;

		using RenderTargetVec = std::vector<RenderTarget*>;
		RenderTargetVec		mRenderTargets;

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

		GlobalConstBuffer	*mGlobalConstBuffer;		
		
	};

	inline DX::Dx11* Graphic::GetDx11(){
		return mDx;
	}
	inline FeatureLevel Graphic::GetDXFeatureLevel() const{
		return mInitParam.featureLevel;
	}

}
#endif
