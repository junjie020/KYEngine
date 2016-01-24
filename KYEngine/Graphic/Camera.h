#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Graphic/SpaceNode.h"
#include "Graphic/Frustum.h"
#include "Math/Matrix.h"

namespace KY
{
	class Camera : public SpaceNode
	{
	public:
		Camera(float fov = 1.570795f, float aspect = 1.0f, float n = 1.0f, float f = 1000.0f);
		Camera(bool ortho, float w, float h, float n, float f);

		bool IsOrtho() const {
			return mOrtho;
		}

		virtual void SetPosition(const Vec4f &pos) override;
		virtual void SetDirection(const Vec4f &dir) override;
		virtual void SetScale(const Vec4f &scale) override;

		const Mat4x4F& GetViewMat() const {
			UpdateRelatedMatrix();
			return mMatView;
		}

		const Mat4x4F& GetProjMat() const {
			UpdateRelatedMatrix();
			return mMatProj;
		}

		const Mat4x4F& GetViewProjMat() const {
			UpdateRelatedMatrix();
			return mMatViewProj;
		}

	private:
		void UpdateRelatedMatrix() const;

	private:
		mutable Frustum mFrustum;

		mutable Mat4x4F	mMatView;
		mutable Mat4x4F	mMatProj;
		mutable Mat4x4F mMatViewProj;

		mutable bool	mDirty;

		bool	mOrtho;
		
	};
}
#endif	//__CAMERA_H__
