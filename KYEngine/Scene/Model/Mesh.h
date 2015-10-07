#ifndef _MESH_H_
#define _MESH_H_

#include "Graphic/RenderOperation.h"

namespace KY
{
    class Mesh
    {
    public:
    	Mesh();
    	~Mesh();

		RenderOperation& GetRO(){ return m_ro; }

    protected:
    	

    private:
		RenderOperation m_ro;
    };
}
#endif // _MESH_H_