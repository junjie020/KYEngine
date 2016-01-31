#ifndef _PIPELINESTAGE_H_
#define _PIPELINESTAGE_H_
#include "Graphic/GraphicDef.h"
#include "Graphic/DX/Dx11PipelineStage.h"

namespace KY
{
	namespace DX
	{
		class Dx11IAStage;
		class Dx11VSStage;
		//class Dx11HSStage;
		//class Dx11TSStage;
		//class Dx11DSStage;
		//class Dx11SOStage;
		class Dx11RSStage;
		class Dx11PSStage;
		class Dx11OMStage;
	}

	class RasterizerStateObj;
	class DepthStencilStateObj;
	class BlendStateObj;

    class PipelineStage
    {
    public:
		PipelineStage() : mIA(nullptr){}
		virtual ~PipelineStage(){}

	protected:
		union{
			DX::Dx11IAStage *mIA;
			DX::Dx11VSStage *mVS;
			DX::Dx11RSStage *mRS;
			DX::Dx11PSStage *mPS;
			DX::Dx11OMStage *mOM;
		};
    };

	enum StageType
	{
		ST_IA = 0,
		ST_VS,
		ST_HS,
		ST_TS, 
		ST_DS, 
		ST_GS,
		ST_SO,
		ST_RS,
		ST_PS,
		ST_OM,

		ST_Count,
	};

	class InputLayout;
	class Resource;
	class Shader;
	class VertexBuffer;
	class IndexBuffer;

	class IAStage : public PipelineStage
	{
	public:
		IAStage();
		~IAStage();
		enum {Type = ST_IA};
		void SetInputLayout(const InputLayout *il);
		void SetPrimitiveType(PrimitiveType type);
		void SetVertexBuffer(const VertexBuffer *vb, const BufferInfo &info);
		void SetIndexBuffer(const IndexBuffer *ib, const BufferInfo &info);
	};

	class VSStage : public PipelineStage
	{
	public:
		VSStage();
		~VSStage();

		enum { Type = ST_VS };

		void SetShader(const Shader *shader);
		void SetConstBuffer(const Buffer &buffer, BufferInfo &info);
	};

	class HSStage : public PipelineStage
	{
	public:
		enum { Type = ST_HS };
	};

	class TSStage : public PipelineStage
	{
	public:
		enum { Type = ST_TS };
	};

	class DSStage : public PipelineStage
	{
	public:
		enum { Type = ST_DS };
	};

	class GSStage : public PipelineStage
	{
	public:
		enum { Type = ST_GS };
	};

	class SOStage : public PipelineStage
	{
	public:
		enum { Type = ST_SO };
	};

	class Viewport;
	class RSStage : public PipelineStage
	{
	public:
		RSStage();
		~RSStage();

		enum { Type = ST_RS };
		void SetViewPort(const Viewport *v);
		void SetRasterizerState(const RasterizerStateObj *obj);

	};

	class PSStage : public PipelineStage
	{
	public:
		PSStage();
		~PSStage();

		enum { Type = ST_PS };

		void SetShader(const Shader *shader);
		void SetConstBuffer(const Buffer &buffer, BufferInfo &info);
	};

	class OMStage : public PipelineStage
	{
	public:
		OMStage();
		~OMStage();
		enum {Type = ST_OM };
		void SetDepthStencilState(const DepthStencilStateObj *obj);
		void SetBlendState(const BlendStateObj *obj);
		
	};
}
#endif // _PIPELINESTAGE_H_