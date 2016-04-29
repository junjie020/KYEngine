#ifndef _VECTOR4_H_
#define _VECTOR4_H_

namespace KY
{
#ifdef USING_GLM
	using Vec4f = glm::vec4;
#else //!USING_GLM
	template<typename Type>
	class Vector4
	{
	public:
		Vector4() {}
		Vector4(const Type &_x, const Type &_y, const Type &_z, const Type &_w)
			: x(_x), y(_y), z(_z), w(_w) {}

		~Vector4() {}

		union {
			struct {
				float x, y, z, w;
			};

			float m[4];
		};

		typedef Vector4<Type>	VecType;

		Type Dot(const VecType& rhs) const {
			return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
		}

		VecType Cross(const VecType &rhs) const {
			return VecType(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, w);
		}

		Type SquareLength() const {
			return x * x + y * y + z * z;
		}

		Type Length() const {
			return std::sqrt(SquareLength());
		}

		VecType& Normalize() {
			const Type len = Length();
			return operator/=(len);
		}

		VecType operator*(const Type& scalar) const {
			return VecType(x * scalar, y *scalar, z * scalar, w * scalar);
		}

		VecType& operator*=(const Type& scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		VecType operator/(const Type& scalar) const {
			return VecType(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		VecType& operator/=(const Type& scalar) {
			x /= scalar, y /= scalar, z /= scalar, w /= scalar;
			return *this;
		}

		VecType operator+(const VecType &rhs) const {
			return VecType(x + rhs.x, y + rhs.y, z + rhs.z, w);
		}

		VecType& operator+=(const VecType &rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		VecType operator-(const VecType &rhs) const {
			return VecType(x - rhs.x, y - rhs.y, z - rhs.z, w);
		}

		VecType& operator-=(const VecType &rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		static Vector4<Type>	ZERO;
		static Vector4<Type>	XAXIS;
		static Vector4<Type>	YAXIS;
		static Vector4<Type>	ZAXIS;
		static Vector4<Type>	WAXIS;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename Type>
	Vector4<Type> Vector4<Type>::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

	template<typename Type>
	Vector4<Type>	Vector4<Type>::XAXIS(1.0f, 0.0f, 0.0f, 0.0f);

	template<typename Type>
	Vector4<Type>	Vector4<Type>::YAXIS(0.0f, 1.0f, 0.0f, 0.0f);

	template<typename Type>
	Vector4<Type>	Vector4<Type>::ZAXIS(0.0f, 0.0f, 1.0f, 0.0f);

	template<typename Type>
	Vector4<Type>	Vector4<Type>::WAXIS(0.0f, 0.0f, 0.0f, 1.0f);

	//////////////////////////////////////////////////////////////////////////

	typedef Vector4<float>	Vec4f;
#endif // USING_GLM
	
}

#ifdef USING_GLM
namespace KY
{
	namespace vec4_utils
	{
		extern glm::vec4 XAXIS;
		extern glm::vec4 YAXIS;
		extern glm::vec4 ZAXIS;
		extern glm::vec4 WAXIS;
		extern glm::vec4 ZERO;
	}
}

namespace glm
{
	template<class T, precision P = defaultp>
	tvec4<T, P> cross(tvec4<T, P> const & x, tvec4<T, P> const & y)
	{
		auto result = cross((const tvec3<T, P>&)(x), (const tvec3<T, P>&)(y));
		return tvec4<T, P>(result.x, result.y, result.z, 0.f);
	}
}
#endif // USING_GLM
#endif // _VECTOR4_H_