#ifndef _PLANE_H_
#define _PLANE_H_

#include "Math/Vector3.h"

namespace KY
{
    class Plane
    {
	public:
		union {
			struct {
				float x, y, z;
			};
			Vec3f v;
		};
		float dist;

    public:
		Plane(){}
		Plane(float _x, float _y, float _z, float d) : x(_x), y(_y), z(_z), dist(d){}

		Vec3f interset(const Plane &p0, const Plane &p1);

    };
}
#endif // _PLANE_H_