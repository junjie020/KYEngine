#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/Resource/IResourceInterface.h"
#include "Graphic/HI/DX/Buffer/DX11Buffer.h"

namespace KY
{
	class Buffer : public Resource
		, public IResourceInterface<DX::DX11Buffer>
	{
	public:
		Buffer(ResourceType type);		

		bool Map(ResourceMapParam &param);
		void UnMap(uint32 subRes);

		bool Init(const BufferParam &param, const ResourceData &resData);		

		const BufferParam& GetBufferParam() const;
	};
}
#endif //_BUFFER_H_