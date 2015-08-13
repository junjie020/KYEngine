#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "Graphic/GraphicDef.h"
namespace KY
{
    class Resource
    {
    public:
		Resource(ResourceType type) : mResType(type){}
		virtual ~Resource(){}
   
		ResourceType GetResourceType() const { return mResType;  }
		
	protected:
		ResourceType mResType;
    };
}
#endif // _RESOURCE_H_