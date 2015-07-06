#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GraphicDef.h"
#include "Common/Singleton.h"
#include "RenderCommandQueue.h"
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

	////////////////////////////////////////////////////////////////////////////////
	// Class name: Graphic
	////////////////////////////////////////////////////////////////////////////////


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

	private:
		bool Render();
		void CommitRenderData();

	private:
		DX::Dx11			*mDx;
		RenderCommandQueue	*mQueue;
	};

	inline DX::Dx11* Graphic::GetDx11(){
		return mDx;
	}
}
#endif