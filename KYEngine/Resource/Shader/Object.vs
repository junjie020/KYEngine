#include "ShadeInput.inc"
#include "Common.inc"

PSInput main(VSInput i)
{
	PSInput psIN = (PSInput)0;

	float4 posWS = mul(transMatrix.world, i.position);	 
	float4 posVS = mul(transMatrix.view, posWS);	
	psIN.positionInVS = posVS.xyz;

	psIN.position = mul(transMatrix.proj, posVS);

	float4 normalWS = mul(transMatrix.world, float4(i.normal, 0.f));
	psIN.normalInVS	= mul(transMatrix.view, normalWS).xyz;

	return psIN;
}