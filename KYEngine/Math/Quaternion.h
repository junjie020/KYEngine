#ifndef _QUATERNION_H_
#define _QUATERNION_H_

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
    };

	typedef Quaternion<float> QuatF;
}
#endif // _QUATERNION_H_