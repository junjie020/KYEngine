#pragma once
#include "Graphic/GraphicDef.h"
#include "Graphic/Resource/Buffer/Buffer.h"


namespace KY
{
	class GlobalConstBuffer
	{
	public:
		GlobalConstBuffer();
		~GlobalConstBuffer();

		void UpdateBuffers();
		template<class BufferType>
		void AddConstBuffer(const BufferType &buffer, ShaderType whichShader, const BufferParam &param)
		{

		}

		using BufferArray = std::unordered_map<ShaderType, Buffer>;
		const BufferArray& GetBuffers() const {
			return mBuffers;
		}
	
	private:
		
		BufferArray mBuffers;
	};
}
