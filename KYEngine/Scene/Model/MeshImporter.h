#ifndef _MESHIMPORTER_H_
#define _MESHIMPORTER_H_

namespace KY
{
	class Mesh;
    class MeshImporter
    {
    public:
		MeshImporter(Mesh *m) : m_Mesh(m){}
		~MeshImporter(){}

		virtual bool Import(const std::string &filename) = 0;

    protected:
		Mesh *m_Mesh;

    private:

    };
}
#endif // _MESHIMPORTER_H_