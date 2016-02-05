struct Input
{
	float4 position : POSITION0;
	//float4 color	: COLOR0;
	float3 normal	: NORMAL0;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color	: COLOR0;
	float3 normal	: NORMAL0;
};

cbuffer MatBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	//matrix matViewProj;
};

Output main(Input i)
{
	Output o = (Output)0;

	o.position = mul(matWorld, i.position);
	o.position = mul(matView, o.position);
	o.position = mul(matProj, o.position);

	o.color = float4(1.0f, 0.0f, 0.0f, 1.0f);//i.color;
	o.normal = i.normal;

	return o;
}