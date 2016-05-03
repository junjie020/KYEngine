#include "stdafx.h"

#include "Matrix.h"
#include "Matrix.inl"


namespace KY
{
	namespace mat4x4_utils
	{
		glm::mat4x4 INDENTIFY(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		glm::mat4x4 ZERO(
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f);
	}
}