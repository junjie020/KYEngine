#ifndef _DX11PIPELINESTAGE_H_
#define _DX11PIPELINESTAGE_H_

#include "Graphic/GraphicDef.h"
namespace KY
{
	class InputLayout;
	class Shader;
	
	namespace DX
	{
		class Dx11IAStage
		{
		public:
			void SetInputLayout(const InputLayout &il);
			void SetPrimitiveType(PrimitiveType pt);

		};

		class Dx11VSStage
		{
		public:
			void SetShader(const Shader &shader);
		};

		class Dx11RSStage
		{
		public:
			void SetState();

		};

		class Dx11PSStage
		{
		public:
			void SetShader(const Shader &shader);
		};

		class Dx11OMStage
		{
		public:
			void SetDepthStencilState();
			void SetBlendState();
		};
	}
}
#endif //_DX11PIPELINESTAGE_H_