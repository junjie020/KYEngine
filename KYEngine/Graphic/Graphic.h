////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


//////////////
// INCLUDES //
//////////////
#include "GraphicDef.h"


/////////////
// GLOBALS //
/////////////

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


	class Graphic
	{
	public:
		Graphic();
		Graphic(const Graphic&);
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