#include "stdafx.h"
#include "Plane.h"
namespace KY
{	
	KY::Vec3f Plane::interset(const Plane &p)
	{
		auto nor = v.Cross(p.v);

		nor.Normalize();


		return Vec3f(0, 0, 0);
	}

}