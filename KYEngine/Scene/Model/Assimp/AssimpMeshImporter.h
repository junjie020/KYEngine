#ifndef _ASSIMPMESHIMPORTER_H_
#define _ASSIMPMESHIMPORTER_H_

#include "Scene/Model/MeshImporter.h"
#include "assimp/Importer.hpp"

namespace KY
{
    class AssimpMeshImporter : public MeshImporter
    {
    public:
		AssimpMeshImporter();
		~AssimpMeshImporter();

		bool Import(const std::string &filename);

    protected:
    	

    private:

    };
}
#endif // _ASSIMPMESHIMPORTER_H_