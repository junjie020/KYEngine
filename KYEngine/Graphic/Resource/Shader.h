#ifndef _SHADER_H_
#define _SHADER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/GraphicDef.h"
namespace KY
{
	namespace DX
	{
		class Dx11Shader;
	}
	class ShaderView
	{
	public:

	};

    class Shader : public Resource
    {
    public:
		Shader();
    	virtual ~Shader();

		bool InitFromFile(ShaderType type, const fs::path &file, const std::string &entry);
		bool InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry);

		ShaderType GetType() const;

    private:		
		DX::Dx11Shader	*mShaderImpl;
    };
}
#endif // _SHADER_H_