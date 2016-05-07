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

		void ConstructAsOrtho(float w, float h, float n, float f);
		void ConstructAsPrespective(float fov, float aspect, float n, float f);

		virtual void SetPosition(const glm::vec4 &pos) override;
		virtual void SetDirection(const glm::vec4 &dir) override;
		virtual void SetScale(const glm::vec4 &scale) override;
		virtual void SetWorldMat(const glm::mat4x4 &matWorld) override;

		const Mat4x4F& GetViewMat() const {			
			return mMatView;
		}

		const Mat4x4F& GetProjMat() const {			
			return mMatProj;
		}

		const Mat4x4F& GetViewProjMat() const {			
			return mMatViewProj;
		}

		void SetUpVector(const glm::vec4 &up) {
			mUpVector = up;
			mDirty = true;
		}

		void UpdateRelatedMatrix();

	private:
		glm::vec4 mUpVector;
		Frustum mFrustum;

		glm::mat4x4	mMatView;
		glm::mat4x4	mMatProj;
		glm::mat4x4 mMatViewProj;

		bool	mDirty;

		bool	mOrtho;
		
	};
}
#endif	//__CAMERA_H__
