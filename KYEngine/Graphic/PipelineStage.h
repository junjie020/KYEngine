#ifndef _PIPELINESTAGE_H_
#define _PIPELINESTAGE_H_

namespace KY
{
    class PipelineStage
    {
    public:
    	PipelineStage();
    	~PipelineStage();

    	

    protected:
    	

    private:

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

	class IAStage : public PipelineStage
	{
	public:

	};

	class VSStage : public PipelineStage
	{
	public:

	};

	class HSStage : public PipelineStage
	{
	public:

	};

	class TessStage : public PipelineStage
	{
	public:

	};

	class DSStage : public PipelineStage
	{
	public:

	};

	class GSStage : public PipelineStage
	{
	public:

	};

	class SOStage : public PipelineStage
	{
	public:

	};

	class Viewport;
	class RSStage : public PipelineStage
	{
	public:
		void SetViewPort(Viewport *v);

	};

	class PSStage : public PipelineStage
	{
	public:

	};

	class OMStage : public PipelineStage
	{
	public:

	};
}
#endif // _PIPELINESTAGE_H_