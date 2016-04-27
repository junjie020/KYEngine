#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace KY
{
	template<typename Type>
    class Vector2
    {
    public:
		union {
			struct{
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

		Vector2(){}
		Vector2(Type e0, Type e1) : x(e0), y(e1){}

		~Vector2(){}

		Type square_length() { return (x * x + y * y); }
		Type length(){ return std::sqrt(square_length()); }
		
		typedef Vector2<Type> ThisType;

		Type dot(const ThisType& rhs){
			return x * rhs.x + y * rhs.y;
		}

		ThisType operator*(Type scalar) const {
			return Vector2<Type>(x * scalar, y *scalar);
		}

		ThisType operator/(Type scalar) const {
			return operator*(1 / scalar);
		}

		ThisType& operator*=(Type scalar){
			x *= scalar, y *= scalar;
			return *this;
		}

		ThisType& operator/=(Type scalar){
			return operator*=(1 / scalar);
		}

    };

	typedef Vector2<float>	Size2F;
	typedef Vector2<uint32> Size2U;

	typedef Vector2<float>	Range2F;
	typedef Vector2<uint32>	Range2U;

	typedef Vector2<float>	Pos2F;
	typedef Vector2<uint32> Pos2U;
	typedef Vector2<int32>  Pos2I;

}
#endif // _VECTOR2_H_