#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

namespace KY
{
    namespace MathUtils
    {
#define	PI			3.1415926535897932384626
#define PI_TWO		2*PI
#define PI_Half		PI / 0.5

		template<typename Type>
		Type ToRadian(Type degree){
			return degree / Type(PI);
		}

		template<typename Type>
		Type ToDegree(Type radian){
			return radian / 180;
		}

    };
}
#endif // _MATHUTILS_H_