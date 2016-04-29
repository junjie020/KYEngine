#ifndef _QUATERNION_H_
#define _QUATERNION_H_


#include "Math/Matrix.h"
#include "Math/MathUtils.h"

namespace KY
{
	template<typename Type>
    class Quaternion
    {
	public:
		Type x, y, z, w;
    };

	typedef Quaternion<float> QuatF;
}
#endif // _QUATERNION_H_