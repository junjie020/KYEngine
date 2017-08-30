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
	struct GlobalDynamicConstBuffer
	{
		struct TransformMatrix {
			Mat4x4F world;
			Mat4x4F view;
			Mat4x4F proj;
		};

		TransformMatrix matrix;
		glm::vec4		eyePos;	// use xyz element
	};

	struct GlobalStaticConstBuffer
	{
		int32		lightNum;
		int32		padding[3];
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
}
#endif // _CONSTBUFFERDEF_H_
