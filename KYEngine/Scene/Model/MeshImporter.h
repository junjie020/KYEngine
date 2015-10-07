#ifndef _MESHIMPORTER_H_
#define _MESHIMPORTER_H_

namespace KY
{
	class Model;
    class MeshImporter
    {
    public:
		MeshImporter(Model *m) : m_Model(m){}
		~MeshImporter(){}

		virtual bool Import(const fs::path &filename) = 0;

    protected:
		Model *m_Model;

    private:

    };
}
#endif // _MESHIMPORTER_H_