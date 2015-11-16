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
		Vec4f GetPostion() const {
			return mWorldMat.Row(3);
		}
		void SetPosition(const Vec4f &pos) {
			mWorldMat.Row(3) = pos;
		}

		Vec4f GetDirection() const {
			return Vec4f::ZAXIS * mWorldMat;
			//return Vec4f();
		}
		void SetDirection(const Vec4f &dir) {
			auto xDir = Vec4f::YAXIS.Cross(dir).Normalize();
			auto yDir = dir.Cross(xDir).Normalize();

			auto xDirLength = mWorldMat.Row(0).Length();
			auto yDirLength = mWorldMat.Row(1).Length();
			auto zDirLength = mWorldMat.Row(2).Length();

			mWorldMat = Mat4x4F(xDir * xDirLength, 
								yDir * yDirLength, 
								Vec4f(dir).Normalize() * zDirLength, 
								mWorldMat.Row(3));
		}

		Vec4f GetScale() const {
			return Vec4f(mWorldMat.Row(0).Length(),
				mWorldMat.Row(1).Length(),
				mWorldMat.Row(2).Length(), 1.0f);
		}
		void SetScale(const Vec4f &scale)
		{
			mWorldMat.Row(0).Normalize() *= scale.x;
			mWorldMat.Row(1).Normalize() *= scale.y;
			mWorldMat.Row(2).Normalize() *= scale.z;
		}


	protected:
		Mat4x4F	mWorldMat;
	};
}

#endif  //__SPACENODE_H__
