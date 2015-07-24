#ifndef _PIPELINESTAGE_H_
#define _PIPELINESTAGE_H_
#include "Graphic/GraphicDef.h"
namespace KY
{
    class PipelineStage
    {
    public:
		PipelineStage(){}
		~PipelineStage(){}
    };

	enum StageType
	{
		ST_IA = 0,
		ST_VS,
		ST_HS,
		ST_TESS, 
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
	class IAStage : public PipelineStage
	{
	public:
		enum {Type = ST_IA};
		void SetInputLayout(const InputLayout &il);
		void SetPrimitiveType(PrimitiveType type);
		void SetBuffer(const Resource &buffer);
	};

	class VSStage : public PipelineStage
	{
	public:
		enum { Type = ST_VS };
	};

	class HSStage : public PipelineStage
	{
	public:
		enum { Type = ST_HS };
	};

	class TessStage : public PipelineStage
	{
	public:
		enum { Type = ST_TESS };
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

	class RasterizerStateObj;

	class Viewport;
	class RSStage : public PipelineStage
	{
	public:
		enum { Type = ST_RS };
		void SetViewPort(Viewport *v);

	};

	class PSStage : public PipelineStage
	{
	public:
		enum { Type = ST_PS };
	};

	class DepthStencilStateObj;
	class BlendStateObj;
	class OMStage : public PipelineStage
	{
	public:
		enum {Type = ST_OM };

		
	};
}
#endif // _PIPELINESTAGE_H_