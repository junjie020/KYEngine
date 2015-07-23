#ifndef _SHADER_H_
#define _SHADER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/GraphicDef.h"
namespace KY
{
	namespace DX
	{
		class Dx11Shader;
		class DX11InputLayout;
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
	
		const DX::Dx11Shader* GetInternal() const { return mShaderImpl; }
    private:
		DX::Dx11Shader	*mShaderImpl;
    };

	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void AddElem(const InputElemDesc &elems);
		DX::DX11InputLayout* GetInternal() { return mLayout;  }
		const DX::DX11InputLayout* GetInternal() const { return mLayout; }
	private:
		DX::DX11InputLayout *mLayout;
	};
}
#endif // _SHADER_H_