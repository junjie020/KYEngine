cbuffer MatrixBuffer : register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	//matrix matViewProj;

	float3	eyePos;
};

cbuffer MaterialBuffer : register(b1)
{
	float4		materialDiffColor;	
	float4		materialSpecularColor;
	float4		ambientColor;
	float4		emissiveColor;
	float		specularPow;
};


