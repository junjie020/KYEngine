struct Input
{
	float4 position : POSITION0;
	float2 tex : TEXCOORD0;
};

struct Output
{
	float4 position : SV_POSITION;
	float2 tex		: TEXCOORD0;
};

cbuffer MatBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
};


Output main(Input i)
{
	Output o;
	o.position = mul(matWorld, i.position);
	o.position = mul(matView, o.position);
	o.position = mul(matProj, o.position);

	o.tex = i.tex;

	return o;
}
