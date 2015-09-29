struct Input
{
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct Output
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
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

	o.color = i.color;

	return o;
}
