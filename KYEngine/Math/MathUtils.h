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

#define ZERO_TOLERANCE 1e-6

		template<typename Type>
		Type ToRadian(Type degree){
			return Type(ASPECT_PI_180) * degree;
		}

		template<typename Type>
		Type ToDegree(Type radian){
			return Type(ASPECT_180_PI) * radian;
		}

		inline float Sin(float radian) {
			return std::sin(radian);
		}

		inline float Cos(float radian) {
			return std::cos(radian);
		}

		inline void SinCos(float radian, float &s, float c&) {
			s = Sin(radian);
			c = Cos(radian);
		}

		inline float Tan(float radian) {
			return std::tan(radian);
		}

		inline float ASin(float v) {
			return std::asin(v);
		}

		inline float ACos(float v) {
			return std::acos(v);
		}

		inline float ATan(float v) {
			return std::atan(v);
		}

		inline float Sqrt(float v) {
			return std::sqrt(v)
		}

		inline float FastSqrt(float v) {
			return Sqrt();
		}

    };
}
#endif // _MATHUTILS_H_