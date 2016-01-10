#ifndef __VECTOR3_H__
#define __VECTOR3_H__

namespace KY
{
	template<typename T>
	class Vector3
	{
	public:
		union {
			struct {
				float x, y, z;
			};

			float m[3];
		};

	public:
		Vector3(T && _x, T && _y, T && _z)
			: x(_x)
			, y(_y)
			, z(_z)
		{}

		void Normalize()
		{
			const float len = Length();
			x /= len;
			y /= len;
			z /= len;
		}

		float SquareLength() const 
		{
			return x * x + y * y + z * z;
		}

		float Length() const
		{
			std::sqrt(SquareLength());
		}

		Vector3<T> Cross(const Vector3<T> &rhs) const {
			return Vector3<T>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}
	};

	using Vec3f = Vector3<float>;
}

#endif // !__VECTOR3_H__

