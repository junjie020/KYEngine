

#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

struct Light
{
	float4	positionInVS;	// point and spot light
	float4  directionInVS;	// spot light
	float4	color;			
	float	intensity;
	float	angle;			// spot
	float	range;			// point and spot light
	int		lightType;		
};

struct LightResult
{
	float4 diffuse;
	float4 specular;
};

StructuredBuffer<Light> Lights : register( t8 );	// reserve t0 ~ t7 for texture sample

float4 CalcSpecularPhong(float4 color, float3 L, float3 N, float3 V)
{
	float3 R = normalize(reflect(-L, N));
	float RdotV = max(0, dot(R, V));

	return color * pow(RdotV, materialSpecularPow);
}

float4 CalcSpecularBlinPhong(float4 color, float3 L, float3 N, float3 V)
{
	float3 H = normalize(L + V);

	float HdotN = max(0, dot(H, N));

	return color * pow(HdotN, materialSpecularPow);
}

float4 CalcDiffuse(float4 color, float3 L, float3 N)
{
	float LdotN = max(0, dot(L, N));
	return color * LdotN;
}

float CalcAttenuation(float distance, float validRange)
{
	return 1 - saturate(distance / validRange);
	//return 1 - smoothstep(0, validRange, distance);
}


LightResult DoDirectionalLighting(Light light, float3 posInVS, float3 normalInVS, float3 eyePosInVS)
{
	LightResult result = (LightResult)0;

	float3 lightVec = normalize(light.positionInVS.xyz - posInVS);
	result.diffuse = CalcDiffuse(light.color, lightVec, normalInVS) * light.intensity;

	float3 viewVecInVS = normalize(eyePosInVS - posInVS);
	result.specular = CalcSpecularBlinPhong(light.color, lightVec, normalInVS, viewVecInVS) * light.intensity;

	return result;
}

LightResult DoPointLihgting(Light light, float3 posInVS, float3 normalInVS, float3 eyePosInVS)
{
	LightResult result = (LightResult)0;

	float3 viewVecInVS = eyePosInVS - posInVS;
	float distance = length(viewVecInVS);
	viewVecInVS /= distance;

	float attenuation = CalcAttenuation(distance, light.range);

	float3 lightVec = normalize(light.positionInVS.xyz - posInVS);
	result.diffuse = CalcDiffuse(light.color, lightVec, normalInVS) * light.intensity * attenuation;

	result.specular = CalcSpecularBlinPhong(light.color, lightVec, normalInVS, viewVecInVS) * light.intensity * attenuation;
	return result;
}

float CalcSpotCoreIntensity(float maxAngle, float3 lightDirectionInVS, float3 lightVecInVS)
{
	float halfAngle = maxAngle * 0.5f;
	float cosMaxAngle = cos(radians(halfAngle));
	float halfCosValue = lerp(cosMaxAngle, 1, 0.5f);

	float lightDotValue = max(0, dot(lightDirectionInVS, lightVecInVS));

	return 1 - saturate(halfCosValue / lightDotValue);
	//return 1 - smoothstep(cosMaxAngle, halfCosValue, lightDotValue);
}

LightResult DoSpotLihgting(Light light, float3 posInVS, float3 normalInVS, float3 eyePosInVS)
{
	LightResult result = (LightResult)0;

	float3 viewVecInVS = eyePosInVS - posInVS;
	float distance = length(viewVecInVS);
	viewVecInVS /= distance;

	float attenuation = CalcAttenuation(distance, light.range);

	float3 lightVec = normalize(light.positionInVS.xyz - posInVS);
	result.diffuse = CalcDiffuse(light.color, lightVec, normalInVS) * light.intensity * attenuation;

	float spotIntensity = CalcSpotCoreIntensity(light.angle, light.directionInVS.xyz, lightVec);

	result.specular = CalcSpecularBlinPhong(light.color, lightVec, normalInVS, viewVecInVS) * light.intensity * attenuation * spotIntensity;
	return result;
}

LightResult DoLighting(float3 posInVS, float3 normalInVS)
{
	const float3 eyePosInVS = (float3)0.f;

	LightResult lResults = (LightResult)0;
	for (int ii = 0; ii < numLights; ++ii)
	{
		LightResult result = (LightResult)0;
		if (Lights[ii].lightType == DIRECTIONAL_LIGHT)
		{
			result = DoDirectionalLighting(Lights[ii], posInVS, normalInVS, eyePosInVS);
		}
		else if (Lights[ii].lightType == POINT_LIGHT)
		{
			result = DoPointLihgting(Lights[ii], posInVS, normalInVS, eyePosInVS);
		}
		else if (Lights[ii].lightType == SPOT_LIGHT)
		{
			result = DoSpotLihgting(Lights[ii], posInVS, normalInVS, eyePosInVS);
		}

		lResults.diffuse = result.diffuse;
		lResults.specular = result.specular;
	}

	return lResults;
}