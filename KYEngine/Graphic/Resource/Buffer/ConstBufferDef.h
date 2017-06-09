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

	struct StaticLightConstBuffer {
		ColorF	diffColor;
		ColorF  ambientColor;
		Vec4f	eyePos;
		Vec4f	lightVec;		
	};

	struct StaticMaterialConstBuffer {
		ColorF	diffColor;
		float	specularPow;
		float	padding[3];
	};
}
#endif // _CONSTBUFFERDEF_H_
