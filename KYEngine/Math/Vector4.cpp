#include "stdafx.h"
#include "Vector4.h"

#ifdef USING_GLM
namespace KY
{
	namespace vec4_utils
	{
		glm::vec4 XAXIS(1.f, 0.f, 0.f, 0.f);
		glm::vec4 YAXIS(0.f, 1.f, 0.f, 0.f);
		glm::vec4 ZAXIS(0.f, 0.f, 1.f, 0.f);
		glm::vec4 WAXIS(0.f, 0.f, 0.f, 1.f);
		glm::vec4 ZERO(0.f, 0.f, 0.f, 0.f);
	}
}
#endif // USING_GLM

