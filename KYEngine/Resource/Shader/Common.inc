cbuffer MatrixBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	//matrix matViewProj;
};

cbuffer MaterialBuffer : register(b1)
{
	float4		materialDiffColor;	
	float4		materialSpecularColor;
	float4		materialAmbientColor;
	float4		materialEmissiveColor;
	float		materialSpecularPow;
};

cbuffer LightInfoBuffer : register(b2)
{
	float3	eyePos;
	int		numLights;
};