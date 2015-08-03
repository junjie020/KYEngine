#ifndef _DX11PIPELINESTAGE_H_
#define _DX11PIPELINESTAGE_H_

#include "Graphic/GraphicDef.h"

#include "Graphic/Resource/StateObject.h"
namespace KY
{
	class InputLayout;
	class Shader;
	class VertexBuffer;
	class IndexBuffer;
	class Buffer;

	struct Viewport;


	namespace DX
	{
		class Dx11IAStage
		{
		public:
			void SetInputLayout(const InputLayout *il);
			void SetPrimitiveType(PrimitiveType pt);
			void SetVertexBuffer(const VertexBuffer *vb, const BufferInfo &info);
			void SetIndexBuffer(const IndexBuffer *ib, const BufferInfo &info);
		};

		class Dx11VSStage
		{
		public:
			void SetShader(const Shader *shader);
			void SetConstBuffer(const Buffer &buffer, const BufferInfo &info);
		};

		class Dx11RSStage
		{
		public:
			void SetViewPort(const Viewport *vp);
			void SetRasterizerState(const RasterizerStateObj *obj);

		};

		class Dx11PSStage
		{
		public:
			void SetShader(const Shader *shader);
			void SetConstBuffer(const Buffer &buffer, const BufferInfo &info);
		};

		class Dx11OMStage
		{
		public:
			void SetDepthStencilState(const DepthStencilStateObj *obj);
			void SetBlendState(const BlendStateObj *obj);
		};
	}
}
#endif //_DX11PIPELINESTAGE_H_