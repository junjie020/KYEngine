#pragma once

#ifndef __SPACENODE_H__
#define __SPACENODE_H__

#include "Math/Vector4.h"
#include "Math/Matrix.h"

namespace KY
{
	class SpaceNode
	{
	public:
		virtual ~SpaceNode() {}

		Vec4f GetPostion() const {
			return mWorldMat[3];
		}

		virtual void SetPosition(const Vec4f &pos) {
			mWorldMat[3] = pos;
		}

		Vec4f GetDirection() const {
			return mWorldMat[2];
		}

		virtual void SetDirection(const Vec4f &dir) {
			auto xDir = glm::normalize(glm::cross(vec4_utils::YAXIS, dir));
			auto yDir = glm::normalize(glm::cross(dir, xDir));

			auto xDirLength = glm::length(mWorldMat[0]);
			auto yDirLength = glm::length(mWorldMat[1]);
			auto zDirLength = glm::length(mWorldMat[2]);

			mWorldMat = Mat4x4F(xDir * xDirLength, 
								yDir * yDirLength, 
								glm::normalize(dir) * zDirLength, 
								mWorldMat[3]);
		}

		Vec4f GetScale() const {
			return Vec4f(glm::length(mWorldMat[0]),
				         glm::length(mWorldMat[1]),
				         glm::length(mWorldMat[2]),
				         1.0f);
		}

		virtual void SetScale(const Vec4f &scale)
		{
			mWorldMat[0] = glm::normalize(mWorldMat[0]);
			mWorldMat[0] *= scale.x;

			mWorldMat[1] = glm::normalize(mWorldMat[1]);
			mWorldMat[1] *= scale.y;

			mWorldMat[2] = glm::normalize(mWorldMat[2]); 
			mWorldMat[2] *= scale.z;
		}


		const Mat4x4F& GetWorldMat() const {
			return mWorldMat;
		}

	protected:
		Mat4x4F	mWorldMat;
	};
}

#endif  //__SPACENODE_H__
