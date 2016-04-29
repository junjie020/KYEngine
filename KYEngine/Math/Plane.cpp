#include "stdafx.h"
#include "Plane.h"

namespace KY
{
	static inline glm::vec3 plane_interset(const Plane &p0, const Plane &p1, const Plane &p2)
	{
		const glm::vec3 p1p2Cross = glm::cross(p1.v, p2.v);
		
		const float co = glm::dot(p0.v, p1p2Cross);

		// p1 cross p2 can determine a plane, if p0.v dot this plane normal is zero, mean this normal is in the p0 plane, that means it will have infinite points
		if (co == 0.0f)
			return glm::vec3(0.0f, 0.0f, 0.0f);

		const glm::vec3 p2p0Cross = glm::cross(p2.v, p0.v);
		const glm::vec3 p0p1Cross = glm::cross(p0.v, p1.v);

		return (p1p2Cross * p0.dist + p2p0Cross * p1.dist + p0p1Cross * p2.dist) / co;
	}
	glm::vec3 Plane::interset(const Plane &p0, const Plane &p1)
	{
		return plane_interset(*this, p0, p1);
	}

}