#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Graphic/Resource/Resource.h"

namespace KY
{
	namespace DX
	{
		class DX11Buffer;
	}
	class Buffer : public Resource
	{
	public:
		Buffer();
		~Buffer();

		const DX::DX11Buffer* GetInternal() const{ return mBuffer; }

	private:
		DX::DX11Buffer *mBuffer;
	};
}
#endif //_BUFFER_H_