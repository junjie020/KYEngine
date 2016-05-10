#ifndef _SHADERRESOURCEVIEW_H_
#define _SHADERRESOURCEVIEW_H_

#include "Graphic/GraphicDef.h"

namespace KY
{
	class Resource;

	namespace DX
	{
		class Dx11ShaderResourceView;
	}

    class ShaderResourceView
    {
    public:
		ShaderResourceView() 
			: mSRV(nullptr) 
		{}

		~ShaderResourceView();

		bool Init(const SRVParam &param, Resource *res);

		DX::Dx11ShaderResourceView* GetInternal() const {
			return mSRV;
		}
    private:
		DX::Dx11ShaderResourceView *mSRV;
    };
}
#endif // _SHADERRESOURCEVIEW_H_