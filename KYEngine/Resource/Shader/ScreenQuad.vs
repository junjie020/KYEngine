struct Input
{
	float4 position : POSITION0;
	//float4 color : COLOR0;
};

struct Output
{
	float4 position : SV_POSITION;
	//float4 color : COLOR0;
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
	o.position = mul(i.position, matWorld);
	o.position = mul(o.position, matView);
	o.position = mul(o.position, matProj);

	return o;
}
