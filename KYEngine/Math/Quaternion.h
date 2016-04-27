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

    public:
		Quaternion(){}
		Quaternion(const Type &_x, const Type &_y, const Type &_z, const Type &_w)
			: x(_x), y(_y), z(_z), w(_w){}

		~Quaternion(){}

		void Rotate(Type radian)
		{
			Type s, c;
			MathUtils::SinCos(radian, s, c);
			

		}

		void RotateVector(Vector4<Type>& axis)
		{
			Vector4 tmp = axis;

			Quaternion q;

			q.w = (-(x * axis.x) - (y * axis.y) - (z * axis.z));
			q.x = ((w * axis.x) + (y * axis.z) - (z * axis.y));
			q.y = ((w * axis.y) - (x * axis.z) + (z * axis.x));
			q.z = ((w * axis.z) + (x * axis.y) - (y * axis.x));

			tmp.x = ((q.z * axis.y) - (q.w * axis.x) - (q.y * axis.z));
			tmp.y = ((q.x * axis.z) - (q.w * axis.y) - (q.z * axis.x));
			tmp.z = ((q.y * axis.x) - (q.w * axis.z) - (q.x * axis.y));
		}

		Type GetAngle() const
		{
			return w * 2;
		}

		Matrix<Type> ToMatrix()
		{
			Matrix<Type> m;
			ToMatrix(m);

			return m;
		}

		void FromMatrix(const Matrix<Type>& matrix)
		{
			float trace, s;

			trace = matrix.f11 + matrix.f22 + matrix.f33;
			if (trace > 0.0f)
			{
				s = MathUtils::FastSqrt(trace + 1.0f);
				w = s * 0.5f;
				s = 0.5f / s;

				x = (matrix.f32 - matrix.f23) * s;
				y = (matrix.f13 - matrix.f31) * s;
				z = (matrix.f21 - matrix.f12) * s;
			}
			else
			{
				int32 biggest;
				enum { A, E, I };
				if (matrix.f11 > matrix.f22)
				{
					if (matrix.f33 > matrix.f11)
						biggest = I;
					else
						biggest = A;
				}
				else
				{
					if (matrix.f33 > matrix.f11)
						biggest = I;
					else
						biggest = E;
				}

				switch (biggest)
				{
				case A:
					s = FastSqrt(matrix.f11 - (matrix.f22 + matrix.f33) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						x = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f32 - matrix.f23) * s;
						y = (matrix.f12 + matrix.f21) * s;
						z = (matrix.f13 + matrix.f31) * s;
						break;
					}
					// I
					s = FastSqrt(matrix.f33 - (matrix.f11 + matrix.f22) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						z = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f21 - matrix.f12) * s;
						x = (matrix.f31 + matrix.f13) * s;
						y = (matrix.f32 + matrix.f23) * s;
						break;
					}
					// E
					s = FastSqrt(matrix.f22 - (matrix.f33 + matrix.f11) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						y = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f13 - matrix.f31) * s;
						z = (matrix.f23 + matrix.f32) * s;
						x = (matrix.f21 + matrix.f12) * s;
						break;
					}
					break;

				case E:
					s = FastSqrt(matrix.f22 - (matrix.f33 + matrix.f11) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						y = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f13 - matrix.f31) * s;
						z = (matrix.f23 + matrix.f32) * s;
						x = (matrix.f21 + matrix.f12) * s;
						break;
					}
					// I
					s = FastSqrt(matrix.f33 - (matrix.f11 + matrix.f22) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						z = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f21 - matrix.f12) * s;
						x = (matrix.f31 + matrix.f13) * s;
						y = (matrix.f32 + matrix.f23) * s;
						break;
					}
					// A
					s = FastSqrt(matrix.f11 - (matrix.f22 + matrix.f33) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						x = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f32 - matrix.f23) * s;
						y = (matrix.f12 + matrix.f21) * s;
						z = (matrix.f13 + matrix.f31) * s;
						break;
					}
					break;

				case I:
					s = FastSqrt(matrix.f33 - (matrix.f11 + matrix.f22) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						z = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f21 - matrix.f12) * s;
						x = (matrix.f31 + matrix.f13) * s;
						y = (matrix.f32 + matrix.f23) * s;
						break;
					}
					// A
					s = FastSqrt(matrix.f11 - (matrix.f22 + matrix.f33) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						x = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f32 - matrix.f23) * s;
						y = (matrix.f12 + matrix.f21) * s;
						z = (matrix.f13 + matrix.f31) * s;
						break;
					}
					// E
					s = FastSqrt(matrix.f22 - (matrix.f33 + matrix.f11) + 1.0f);
					if (s > ZERO_TOLERANCE)
					{
						y = s * 0.5f;
						s = 0.5f / s;
						w = (matrix.f13 - matrix.f31) * s;
						z = (matrix.f23 + matrix.f32) * s;
						x = (matrix.f21 + matrix.f12) * s;
						break;
					}
					break;

				default:
					assert(0);
				}
			}
		}

		void ToMatrix(Matrix<Type>& matrix)
		{
			float X2, Y2, Z2;
			float XX2, YY2, ZZ2;
			float XY2, XZ2, XW2;
			float YZ2, YW2, ZW2;

			X2 = 2.0f * x;
			XX2 = X2   * x;
			XY2 = X2   * y;
			XZ2 = X2   * z;
			XW2 = X2   * w;

			Y2 = 2.0f * y;
			YY2 = Y2   * y;
			YZ2 = Y2   * z;
			YW2 = Y2   * w;

			Z2 = 2.0f * z;
			ZZ2 = Z2   * z;
			ZW2 = Z2   * w;

			matrix.f11 = 1.0f - YY2 - ZZ2;
			matrix.f12 = XY2 - ZW2;
			matrix.f13 = XZ2 + YW2;

			matrix.f21 = XY2 + ZW2;
			matrix.f22 = 1.0f - XX2 - ZZ2;
			matrix.f23 = YZ2 - XW2;

			matrix.f31 = XZ2 - YW2;
			matrix.f32 = YZ2 + XW2;
			matrix.f33 = 1.0f - XX2 - YY2;

			matrix.f14 = matrix.f24 = matrix.f34 = matrix.f14 = matrix.f42 = matrix.f43 = 0.0f;
			matrix.f44 = 1.0f;
		}
    };

	typedef Quaternion<float> QuatF;
}
#endif // _QUATERNION_H_