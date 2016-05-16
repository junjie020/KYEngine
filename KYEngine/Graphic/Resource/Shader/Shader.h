#ifndef _SHADER_H_
#define _SHADER_H_

#include "Graphic/Resource/Resource.h"
#include "Graphic/GraphicDef.h"

#include "Graphic/Resource/IResourceInterface.h"
#include "Graphic/HI/DX/Shader/Dx11Shader.h"
namespace KY
{
	class Buffer;	
	typedef std::pair<uint32, const Buffer*>	BufferPair;
	typedef std::vector<BufferPair>				ConstBufferVec;

    class Shader : public Resource
		, public IResourceInterface<DX::Dx11Shader>
    {
    public:
		Shader();    	

		bool InitFromFile(ShaderType type, const fs::path &file, const std::string &entry = "main");
		bool InitFromCode(ShaderType type, const std::string &shaderCode, const std::string &entry = "main", const std::string &srcFileName = "");

		ShaderType GetShaderType() const;

		void AddConstBuffer(uint32 bindIdx, const Buffer *buffer) {
			BOOST_ASSERT(std::none_of(std::begin(mConstBuffers), std::end(mConstBuffers), [buffer](const BufferPair &b){return b.second == buffer; }));
			mConstBuffers.push_back(BufferPair(bindIdx, buffer));
		}

		const ConstBufferVec& GetConstBuffers() const { return mConstBuffers; }	

    private:		
		ConstBufferVec	mConstBuffers;
    };

	class InputLayout : public IResourceInterface<DX::DX11InputLayout>
	{
	public:
		void AddElem(const InputElemDesc &elems);
		bool Init(const Shader &vs);

		//DX::DX11InputLayout* GetInternal() { return mDx11Internal;  }		
		void Clean();	
	};
}
#endif // _SHADER_H_