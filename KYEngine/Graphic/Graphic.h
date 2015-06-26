#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GraphicDef.h"
#include "Common/Singleton.h"

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

	private:
		bool Render();

	private:
		DX::Dx11 *m_pDx;
	};
}
#endif