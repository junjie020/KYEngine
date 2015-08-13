#ifndef _SHADER_H_
#define _SHADER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/GraphicDef.h"
namespace KY
{
	class Buffer;
	namespace DX
	{
		class Dx11Shader;
		class DX11InputLayout;
	}
	class ShaderView
	{
	public:

	};

	typedef std::pair<uint32, const Buffer*>	BufferPair;
	typedef std::vector<BufferPair>				ConstBufferVec;

    class Shader : public Resource
    {
    public:
		Shader();
    	virtual ~Shader();

		bool InitFromFile(ShaderType type, const fs::path &file, const std::string &entry = "main");
		bool InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry = "main");

		ShaderType GetShaderType() const;

		bool IsValid() const;

		void AddConstBuffer(uint32 bindIdx, const Buffer *buffer) {
			BOOST_ASSERT(std::none_of(std::begin(mConstBuffers), std::end(mConstBuffers), [buffer](const BufferPair &b){return b.second == buffer; }));
			mConstBuffers.push_back(BufferPair(bindIdx, buffer));
		}

		const ConstBufferVec& GetConstBuffers() const { return mConstBuffers; }

	public:
		// internal
		const DX::Dx11Shader* GetInternal() const { return mShaderImpl; }

    private:
		DX::Dx11Shader	*mShaderImpl;
		ConstBufferVec	mConstBuffers;
    };

	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void AddElem(const InputElemDesc &elems);
		bool Create(const Shader &vs);
		bool IsValid() const;
		DX::DX11InputLayout* GetInternal() { return mLayout;  }
		const DX::DX11InputLayout* GetInternal() const { return mLayout; }
	private:
		DX::DX11InputLayout *mLayout;
	};
}
#endif // _SHADER_H_