struct Input
{
	float4 position : POSITION0;
	//float4 color	: COLOR0;
	float3 normal	: NORMAL0;
};

struct Output
{
	float4 position : SV_POSITION;	
	float3 normal	: NORMAL0;
	float3 positionWS : TEXCOORD0;
};

cbuffer TransformBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	//matrix matViewProj;
};

Output main(Input i)
{
	Output o = (Output)0;

	float4 posWS = mul(matWorld, i.position);
	o.positionWS = posWS.xyz;
	float4 posVS = mul(matView, posWS);	
	
	o.position = mul(matProj, posVS);

	o.normal	= i.normal;

	return o;
}