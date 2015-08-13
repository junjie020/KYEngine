#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/DX/Buffer/DX11Buffer.h"

namespace KY
{
	namespace DX
	{
		class DX11Buffer;
	}
	class Buffer : public Resource
	{
	public:
		Buffer(ResourceType type);
		~Buffer();

		bool Map(ResourceMapParam &param);
		void UnMap(uint32 subRes);

		bool Create(const BufferParam &param, const ResourceData &resData);
		const DX::DX11Buffer* GetInternal() const{ return mBuffer; }

	private:
		DX::DX11Buffer *mBuffer;
	};
}
#endif //_BUFFER_H_