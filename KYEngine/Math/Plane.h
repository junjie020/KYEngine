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
			glm::vec3 v;
		};
		float dist;

    public:
		Plane(){}
		Plane(float _x, float _y, float _z, float d) : x(_x), y(_y), z(_z), dist(d){}

		glm::vec3 interset(const Plane &p0, const Plane &p1);

    };
}
#endif // _PLANE_H_