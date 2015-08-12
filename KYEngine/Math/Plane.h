#ifndef _PLANE_H_
#define _PLANE_H_

namespace KY
{
    class Plane
    {
	public:
		float x, y, z;	// normal
		float dist;

    public:
		Plane(){}
		Plane(float _x, float _y, float _z, float d) : x(_x), y(_y), z(_z), dist(d){}

		~Plane(){}



    };
}
#endif // _PLANE_H_