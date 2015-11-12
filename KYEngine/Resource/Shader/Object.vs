struct Input
{
	float4 position : POSITION0;
	float4 color	: COLOR0;
	float4 normal	: NORMAL0;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color	: COLOR0;
	float4 normal	: NORMAL0;
};

cbuffer MatBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	matrix matViewProj;
};

cbuffer LightBuffer : register(b1)
{
	float3 lightDir;
	float3 eyeDir;
	float4 ambColor;
}


Output main(Input i)
{
	Output o;

	return 0;
}