#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

namespace KY
{
	template<typename Type>
    class Rectangle
    {
    public:
		union {
			struct{
				Type left, top, right, bottom;
			};
			
			Type m[4];
		};

		Rectangle(){}
		Rectangle(Type l, Type t, Type r, Type b) : left(l), top(t), right(r), bottom(b){}

		~Rectangle(){}

		bool isvalid() const {
			return left < right && top < bottom;
		}

		bool isempty() const{
			return left == right && top == bottom;
		}

		Type width() const {
			return (right - left);
		}

		Type height() const {
			return (bottom - top);
		}

		typedef Rectangle<Type> ThisType;
		ThisType& operator*=(Type scalar) {
			left *= scalar, top *= scalar;
			right *= scalar, bottom *= scalar;
			return *this;
		}

		ThisType operator*(Type scalar) const{
			return ThisType(left * scalar, top *scalar,
							right *scalar, bottom *scalar);
		}
    };

	using RectF = Rectangle<float>;
	using RectU = Rectangle<uint32>;
	using RectI = Rectangle<int32>;
}
#endif // _RECTANGLE_H_