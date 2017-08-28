

#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

struct Light
{
	float4	positionInVS;
	float4	color;
	float	intensity;
	float	angle;
	float	range;
	int		lightType;
};

StructuredBuffer<Light> Lights : register( t8 );	// reserve t0 ~ t1 for texture sample

