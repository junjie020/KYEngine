#ifndef _CONSTBUFFERDEF_H_
#define _CONSTBUFFERDEF_H_

#include "Math/Matrix.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Color.h"
//#include "Math/Color.inl"

namespace KY
{
	// need packing into 16bytes
	struct TransformConstBuffer {
		Mat4x4F matWorld;
		Mat4x4F matView;
		Mat4x4F matProj;
	};

	//struct StaticLightConstBuffer {
	//	ColorF	diffColor;
	//	ColorF  ambientColor;
	//	Vec4f	eyePos;
	//	Vec4f	lightVec;		
	//};

	struct StaticMaterialConstBuffer {
		ColorF	diffColor;
		ColorF	specularColor;
		ColorF	ambientColor;
		ColorF  emissiveColor;

		float	specularPow;
		float	padding[3];
	};

	enum class LightType : uint32 {
		Directional,
		Point,
		Spot,
		Unknown
	};

	struct LightElemConstBuffer
	{
		glm::vec4	positionInVS;	// point and spot light
		glm::vec4	directionInVS;	// spot light
		ColorF		color;
		float		intensity;
		float		angle;			// spot
		float		range;			// point and spot light
		LightType	lightType;
	};

	struct GlobalLightInfo
	{
		glm::vec3 eyePos;
		uint32	lightNum;
	};
}
#endif // _CONSTBUFFERDEF_H_
