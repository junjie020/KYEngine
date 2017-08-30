struct TransformMatrix
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;	
};


cbuffer GlobalRenderDynamicBuffer : register(b0)
{
	TransformMatrix transMatrix;
	float3 eyePos;
};

cbuffer GlobalRenderStaticBuffer : register(b1)
{
	int		numLights;
};

struct MaterialData
{
	float4 diffuse;
	float4 specular;
	float4 ambient;
	float4 emissive;
	float	specularPow;
};

cbuffer MaterialBuffer : register(b2)
{
	MaterialData material;
};