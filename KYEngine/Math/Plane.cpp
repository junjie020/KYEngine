#include "stdafx.h"
#include "Plane.h"

namespace KY
{
	static inline Vec3f plane_interset(const Plane &p0, const Plane &p1, const Plane &p2)
	{
		const Vec3f p1p2Cross = p1.v.Cross(p2.v);

		const float co = p0.v.Dot(p1p2Cross);

		// p1 cross p2 can determine a plane, if p0.v dot this plane normal is zero, mean this normal is in the p0 plane, that means it will have infinite points
		if (co == 0.0f)
			return Vec3f(0.0f, 0.0f, 0.0f);

		const Vec3f p2p0Cross = p2.v.Cross(p0.v);
		const Vec3f p0p1Cross = p0.v.Cross(p1.v);

		return (p1p2Cross * p0.dist + p2p0Cross * p1.dist + p0p1Cross * p2.dist) / co;
	}
	KY::Vec3f Plane::interset(const Plane &p0, const Plane &p1)
	{
		return plane_interset(*this, p0, p1);
	}

}