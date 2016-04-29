#ifndef _VECTORUNIT_H_
#define _VECTORUNIT_H_

#include "Vector3.h"
#include "Vector4.h"

namespace KY
{
#ifdef USING_GLM
	
#else //!USING_GLM
	template<typename T>
	Vector4<T> ToVec4(Vector3<T> &&rhs) {
		return Vector4<T>(rhs.x, rhs.y, rhs.z, 1.0f);
	}

	template<typename T>
	Vector3<T> ToVec3(Vector4<T> &&rhs) {
		return *(reinterpret_cast<Vector3<T>*>(&rhs));
	}
#endif // USING_GLM

}

#endif // !_VECTORUNIT_H_
