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


Output main(Input i)
{
	Output o;
	//o.color = float4()//i.color;
	o.position = float4(i.position.xy, 0, 1.0);
	return o;
}
