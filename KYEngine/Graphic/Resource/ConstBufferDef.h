#ifndef _CONSTBUFFERDEF_H_
#define _CONSTBUFFERDEF_H_

#include "Math/Matrix.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Color.h"
//#include "Math/Color.inl"

namespace KY
{
	struct TransformConstBuffer {
		Mat4x4F matWorld;
		Mat4x4F matView;
		Mat4x4F matProj;
	};

	struct StaticLightConstBuffer {
		ColorF	diffColor;
		Vec4f	eyePos;
		Vec4f	lightVec;
	};

	struct StaticMaterialConstBuffer {
		ColorF	diffColor;
	};
}
#endif // _CONSTBUFFERDEF_H_
