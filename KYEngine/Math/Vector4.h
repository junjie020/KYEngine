#ifndef _VECTOR4_H_
#define _VECTOR4_H_

namespace KY
{
	template<typename Type>
    class Vector4
    {
    public:
		Vector4(){}
		Vector4(const Type &_x, const Type &_y, const Type &_z, const Type &_w)
			: x(_x), y(_y), z(_z), w(_w){}

		~Vector4(){}

		union {
			struct {
				float x, y, z, w;
			};

			float m[4];
		};
    };

	typedef Vector4<float>	Vec4f;
}
#endif // _VECTOR4_H_