#ifndef _ASSIMPMESHIMPORTER_H_
#define _ASSIMPMESHIMPORTER_H_

#include "Scene/Model/MeshImporter.h"

namespace KY
{
    class AssimpMeshImporter : public MeshImporter
    {
    public:
		AssimpMeshImporter(Mesh *m);
		~AssimpMeshImporter();

		bool Import(const fs::path &filename);

    protected:
    	

    private:

    };
}
#endif // _ASSIMPMESHIMPORTER_H_