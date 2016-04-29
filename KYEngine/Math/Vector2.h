#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace KY
{
#ifdef USING_GLM
	using Size2F = glm::vec2;
	using Size2U = glm::uvec2;

	using Range2F = glm::vec2;
	using Range2U = glm::uvec2;

	using Pos2F = glm::vec2;
	using Pos2U = glm::uvec2;
	using Pos2I = glm::ivec2;
#else //!USING_GLM
	template<typename Type>
	class Vector2
	{
	public:
		union {
			struct {
				Type x, y;
			};

			struct {
				Type w, h;
			};

			struct {
				Type beg, end;
			};
			Type m[2];
		};

		Vector2() {}
		Vector2(Type e0, Type e1) : x(e0), y(e1) {}

		~Vector2() {}

		Type square_length() { return (x * x + y * y); }
		Type length() { return std::sqrt(square_length()); }

		typedef Vector2<Type> ThisType;

		Type dot(const ThisType& rhs) {
			return x * rhs.x + y * rhs.y;
		}

		ThisType operator*(Type scalar) const {
			return Vector2<Type>(x * scalar, y *scalar);
		}

		ThisType operator/(Type scalar) const {
			return operator*(1 / scalar);
		}

		ThisType& operator*=(Type scalar) {
			x *= scalar, y *= scalar;
			return *this;
		}

		ThisType& operator/=(Type scalar) {
			return operator*=(1 / scalar);
		}

	};

	using Size2F = Vector2<float>;
	using Size2U = Vector2<uint32>;

	using Range2F = Vector2<float>;
	using Range2U = Vector2<uint32>;

	using Pos2F = Vector2<float>;
	using Pos2U = Vector2<uint32>;
	using Pos2I = Vector2<int32>;
#endif // USING_GLM
}
#endif // _VECTOR2_H_