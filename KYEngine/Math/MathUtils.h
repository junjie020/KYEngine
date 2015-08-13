#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

namespace KY
{
    namespace MathUtils
    {
#define	PI			3.1415926535897932384626
#define PI_TWO		2*PI
#define PI_Half		PI / 0.5

#define ASPECT_PI_180	(PI / 180.0)
#define ASPECT_180_PI	(180.0 / PI)

		template<typename Type>
		Type ToRadian(Type degree){
			return Type(ASPECT_PI_180) * degree;
		}

		template<typename Type>
		Type ToDegree(Type radian){
			return Type(ASPECT_180_PI) * radian;
		}

    };
}
#endif // _MATHUTILS_H_