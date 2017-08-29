struct VSInput
{
	float4 position : POSITION0;
	//float4 color	: COLOR0;
	float3 normal	: NORMAL0;
};

struct PSInput
{
	float4 position : SV_POSITION;	
	float3 positionInVS : TEXCOORD0;
	float3 normalInVS	: NORMAL0;	
};