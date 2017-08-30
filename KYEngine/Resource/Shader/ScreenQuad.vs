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
	matrix world;
	matrix view;
	matrix proj;
};


Output main(Input i)
{
	Output o;
	o.position = mul(transMatrix.world, i.position);
	o.position = mul(transMatrix.view, o.position);
	o.position = mul(transMatrix.proj, o.position);

	o.color = i.color;

	return o;
}
