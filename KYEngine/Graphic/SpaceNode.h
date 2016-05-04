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

		glm::vec4 GetPostion() const {
			return mWorldMat[3];
		}

		virtual void SetPosition(const glm::vec4 &pos) {
			mWorldMat[3] = pos;
		}

		glm::vec4 GetDirection() const {
			return mWorldMat[2];
		}

		virtual void SetDirection(const glm::vec4 &dir) {
			auto xDir = glm::normalize(glm::cross(vec4_utils::YAXIS, dir));
			auto yDir = glm::normalize(glm::cross(dir, xDir));

			auto xDirLength = glm::length(mWorldMat[0]);
			auto yDirLength = glm::length(mWorldMat[1]);
			auto zDirLength = glm::length(mWorldMat[2]);

			mWorldMat = glm::mat4x4(xDir * xDirLength, 
								yDir * yDirLength, 
								glm::normalize(dir) * zDirLength, 
								mWorldMat[3]);
		}

		glm::vec4 GetScale() const {
			return glm::vec4(glm::length(mWorldMat[0]),
				         glm::length(mWorldMat[1]),
				         glm::length(mWorldMat[2]),
				         1.0f);
		}

		virtual void SetScale(const glm::vec4 &scale)
		{
			mWorldMat[0] = glm::normalize(mWorldMat[0]);
			mWorldMat[0] *= scale.x;

			mWorldMat[1] = glm::normalize(mWorldMat[1]);
			mWorldMat[1] *= scale.y;

			mWorldMat[2] = glm::normalize(mWorldMat[2]); 
			mWorldMat[2] *= scale.z;
		}

		virtual void SetWorldMat(const glm::mat4x4 &matWorld)
		{
			mWorldMat = matWorld;
		}

		const glm::mat4x4& GetWorldMat() const {
			return mWorldMat;
		}

	protected:
		glm::mat4x4	mWorldMat;
	};
}

#endif  //__SPACENODE_H__
