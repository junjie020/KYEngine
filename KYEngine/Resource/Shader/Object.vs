#include "ShadeInput.inc"
#include "Common.inc"

PSInput main(VSInput i)
{
	PSInput psIN = (PSInput)0;

	float4 posWS = mul(matWorld, i.position);	 
	float4 posVS = mul(matView, posWS);	
	psIN.positionInVS = posVS.xyz;

	psIN.position = mul(matProj, posVS);

	float4 normalWS = mul(matWorld, float4(i.normal, 0.f));
	psIN.normalInVS	= mul(matView, normalWS).xyz;

	return psIN;
}