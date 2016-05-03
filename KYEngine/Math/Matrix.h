#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector4.h"

namespace KY
{
#ifdef USING_GLM
	using Mat4x4F = glm::mat4x4;
#else //!USING_GLM
	// row major
	template<typename Type>
	class Matrix
	{
	public:
		union {
			struct {
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
			float			m[16];
			float			mm[4][4];
		};
	public:
		Matrix() {}
		Matrix(float _m00, float _m01, float _m02, float _m03,
			float _m10, float _m11, float _m12, float _m13,
			float _m20, float _m21, float _m22, float _m23,
			float _m30, float _m31, float _m32, float _m33)
			: m00(_m00), m01(_m01), m02(_m02), m03(_m03)
			, m10(_m10), m11(_m11), m12(_m12), m13(_m13)
			, m20(_m20), m21(_m21), m22(_m22), m23(_m23)
			, m30(_m30), m31(_m31), m32(_m32), m33(_m33)
		{}

		typedef Vector4<Type> VecType;

		Matrix(const VecType &r0, const VecType &r1, const VecType &r2, const VecType &r3)
		{
			memcpy(&Row(0), &r0, sizeof(VecType));
			memcpy(&Row(1), &r1, sizeof(VecType));
			memcpy(&Row(2), &r2, sizeof(VecType));
			memcpy(&Row(3), &r3, sizeof(VecType));
		}

		VecType& Row(uint32 rowIdx) {
			return *(reinterpret_cast<VecType*>(this) + rowIdx);
		}

		const VecType& Row(uint32 rowIdx) const {
			return *(reinterpret_cast<const VecType*>(this) + rowIdx);
		}

		VecType Col(uint32 colIdx) const {
			return VecType(mm[0][colIdx], mm[1][colIdx], mm[2][colIdx], mm[3][colIdx]);
		}

		Type Det() const {
			return	  m00*(m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33) + m13*(m21*m32 - m22*m31))
				- m01*(m10*(m22*m33 - m23*m32) + m12*(m23*m30 - m20*m33) + m13*(m20*m32 - m22*m30))
				+ m02*(m10*(m21*m33 - m23*m31) + m11*(m23*m30 - m20*m33) + m13*(m20*m31 - m21*m30))
				- m03*(m10*(m21*m32 - m22*m31) + m11*(m22*m30 - m20*m32) + m22*(m20*m31 - m21*m30));
		}

		void Inverse() {
			Type invDet = Det();
			if (IS_ZERO(invDet))
			{
				invDet = 1.0f / invDet;

				Matrix<Type>	mat(*this);

				m00 = invDet *
					(mat.m11 * (mat.m22 * mat.m33 - mat.m23 * mat.m32)
						+ mat.m12 * (mat.m23 * mat.m31 - mat.m21 * mat.m33)
						+ mat.m13 * (mat.m21 * mat.m32 - mat.m22 * mat.m31));

				m01 = invDet *
					(mat.m21 * (mat.m02 * mat.m33 - mat.m03 * mat.m32)
						+ mat.m22 * (mat.m03 * mat.m31 - mat.m01 * mat.m33)
						+ mat.m23 * (mat.m01 * mat.m32 - mat.m02 * mat.m31));

				m02 = invDet *
					(mat.m31 * (mat.m02 * mat.m13 - mat.m03 * mat.m12)
						+ mat.m32 * (mat.m03 * mat.m11 - mat.m01 * mat.m13)
						+ mat.m33 * (mat.m01 * mat.m12 - mat.m02 * mat.m11));

				m03 = invDet *
					(mat.m01 * (mat.m13 * mat.m22 - mat.m12 * mat.m23)
						+ mat.m02 * (mat.m11 * mat.m23 - mat.m13 * mat.m21)
						+ mat.m03 * (mat.m12 * mat.m21 - mat.m11 * mat.m22));

				m10 = invDet *
					(mat.m12 * (mat.m20 * mat.m33 - mat.m23 * mat.m30)
						+ mat.m13 * (mat.m22 * mat.m30 - mat.m20 * mat.m32)
						+ mat.m10 * (mat.m23 * mat.m32 - mat.m22 * mat.m33));

				m11 = invDet *
					(mat.m22 * (mat.m00 * mat.m33 - mat.m03 * mat.m30)
						+ mat.m23 * (mat.m02 * mat.m30 - mat.m00 * mat.m32)
						+ mat.m20 * (mat.m03 * mat.m32 - mat.m02 * mat.m33));

				m12 = invDet *
					(mat.m32 * (mat.m00 * mat.m13 - mat.m03 * mat.m10)
						+ mat.m33 * (mat.m02 * mat.m10 - mat.m00 * mat.m12)
						+ mat.m30 * (mat.m03 * mat.m12 - mat.m02 * mat.m13));

				m13 = invDet *
					(mat.m02 * (mat.m13 * mat.m20 - mat.m10 * mat.m23)
						+ mat.m03 * (mat.m10 * mat.m22 - mat.m12 * mat.m20)
						+ mat.m00 * (mat.m12 * mat.m23 - mat.m13 * mat.m22));

				m20 = invDet *
					(mat.m13 * (mat.m20 * mat.m31 - mat.m21 * mat.m30)
						+ mat.m10 * (mat.m21 * mat.m33 - mat.m23 * mat.m31)
						+ mat.m11 * (mat.m23 * mat.m30 - mat.m20 * mat.m33));

				m21 = invDet *
					(mat.m23 * (mat.m00 * mat.m31 - mat.m01 * mat.m30)
						+ mat.m20 * (mat.m01 * mat.m33 - mat.m03 * mat.m31)
						+ mat.m21 * (mat.m03 * mat.m30 - mat.m00 * mat.m33));

				m22 = invDet *
					(mat.m33 * (mat.m00 * mat.m11 - mat.m01 * mat.m10)
						+ mat.m30 * (mat.m01 * mat.m13 - mat.m03 * mat.m11)
						+ mat.m31 * (mat.m03 * mat.m10 - mat.m00 * mat.m13));

				m23 = invDet *
					(mat.m03 * (mat.m11 * mat.m20 - mat.m10 * mat.m21)
						+ mat.m00 * (mat.m13 * mat.m21 - mat.m11 * mat.m23)
						+ mat.m01 * (mat.m10 * mat.m23 - mat.m13 * mat.m20));

				m30 = invDet *
					(mat.m10 * (mat.m22 * mat.m31 - mat.m21 * mat.m32)
						+ mat.m11 * (mat.m20 * mat.m32 - mat.m22 * mat.m30)
						+ mat.m12 * (mat.m21 * mat.m30 - mat.m20 * mat.m31));

				m31 = invDet *
					(mat.m20 * (mat.m02 * mat.m31 - mat.m01 * mat.m32)
						+ mat.m21 * (mat.m00 * mat.m32 - mat.m02 * mat.m30)
						+ mat.m22 * (mat.m01 * mat.m30 - mat.m00 * mat.m31));

				m32 = invDet *
					(mat.m30 * (mat.m02 * mat.m11 - mat.m01 * mat.m12)
						+ mat.m31 * (mat.m00 * mat.m12 - mat.m02 * mat.m10)
						+ mat.m32 * (mat.m01 * mat.m10 - mat.m00 * mat.m11));

				m33 = invDet *
					(mat.m00 * (mat.m11 * mat.m22 - mat.m12 * mat.m21)
						+ mat.m01 * (mat.m12 * mat.m20 - mat.m10 * mat.m22)
						+ mat.m02 * (mat.m10 * mat.m21 - mat.m11 * mat.m20));
			}
		}

		Matrix<Type> ToInverse() const {
			Matrix<Type> mat(*this);
			mat.Inverse();
			return mat;
		}

		void Transpose() {
			std::swap(m01, m10);
			std::swap(m02, m20);
			std::swap(m03, m30);


			std::swap(m12, m22);
			std::swap(m12, m31);

			std::swap(m23, m32);
		}

		Matrix<Type> ToTranspose() {
			Matrix<Type> mat = *this;
			mat.Transpose();

			return mat;
		}

		Matrix<Type> ToTranspose3x3() const {
			Matrix<Type> mat;

			std::swap(mat.m01, mat.m10);
			std::swap(mat.m02, mat.m20);

			std::swap(mat.m12, mat.m21);

			return mat;
		}


		//Matrix operator*=(const Matrix &rhs){
		//	m
		//}

	public:
		static Matrix INDENTIFY;
		static Matrix ZERO;
	};

	using Mat4x4F = Matrix<float>;

	template<typename Type>
	inline 	Vector4<Type> operator*(const Matrix<Type>& mat, const Vector4<Type>& v) {
		// not effective
		const auto col0 = mat.Col(0);
		const auto col1 = mat.Col(1);
		const auto col2 = mat.Col(2);
		const auto col3 = mat.Col(3);

		return Vector4<Type>(col0.Dot(v), col1.Dot(v), col2.Dot(v), col3.Dot(v));
		//const float *f = mat.m;
		//Vector4<Type> vPost;
		//vPost.x = v.x*f[0] + v.y*f[4] + v.z*f[8] + v.w*f[12];
		//vPost.y = v.x*f[1] + v.y*f[5] + v.z*f[9] + v.w*f[13];
		//vPost.z = v.x*f[2] + v.y*f[6] + v.z*f[10] + v.w*f[14];
		//vPost.w = v.x*f[3] + v.y*f[7] + v.z*f[11] + v.w*f[15];

		//return vPost;
	}

	template<typename Type>
	inline 	Vector4<Type> operator*(const Vector4<Type>& v, const Matrix<Type>& mat) {
		// also treat as row vector with row matrix
		return operator*(mat, v);
	}

	template<typename Type>
	inline Matrix<Type> operator*(const Matrix<Type>& lhs, const Matrix<Type> &rhs) {
		return Matrix<Type>(lhs.Row(0) * rhs, lhs.Row(1) * rhs, lhs.Row(2) * rhs, lhs.Row(3) * rhs);
	}

	template<typename Type>
	inline Matrix<Type> ConstructPrespectiveMatrix(Type l, Type r, Type b, Type t, Type n, Type f) {
		/*

		2*zn/(r-l)   0            0              0
		0            2*zn/(t-b)   0              0
		(l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
		0            0            zn*zf/(zn-zf)  0


		*/
		Matrix<Type> m = Matrix<Type>::ZERO;
		m.m00 = 2 * n / (r - l);
		m.m20 = (r + l) / (l - r);

		m.m11 = 2 * n / (t - b);
		m.m21 = (b + t) / (b - t);

		m.m22 = f / (f - n);
		m.m23 = 1;
		m.m32 = n * f / (n - f);

		return m;
	}


	template<typename Type>
	inline Matrix<Type> ConstructPrespectiveMatrix(Type fov /*= 1.570795f*/, Type aspect /*= 1.0f*/, Type n /*= 1.0f*/, Type f /*= 1000.0f*/) {
		const Type height = Type(std::tan(fov / 2));
		const Type width = aspect * height;

		/*
		xScale     0          0               0
		0        yScale       0               0
		0          0       zf/(zf-zn)         1
		0          0       -zn*zf/(zf-zn)     0
		where:
		yScale = cot(fovY/2)

		xScale = yScale / aspect ratio
		*/

		Matrix<Type> m = Matrix<Type>::ZERO;
		m.m00 = 1 / width;

		m.m11 = 1 / height;

		m.m22 = f / (f - n);
		m.m23 = 1;
		m.m32 = n * f / (n - f);

		return m;
	}

	template<typename Type>
	inline Matrix<Type> ConstructOrthoMatrix(Type l, Type r, Type b, Type t, Type n, Type f) {
		/*

		2/(r-l)      0            0           0
		0            2/(t-b)      0           0
		0            0            1/(zf-zn)   0
		(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1

		*/
		Matrix<Type> m = Matrix<Type>::ZERO;
		m.m00 = 2 * (r - l);
		m.m30 = (l + r) / (l - r);

		m.m11 = 2 * (t - b);
		m.m31 = (t + b) / (b - t);

		m.m22 = 1 / (f - n);
		m.m32 = n / (n - f);

		return m;
	}

	template<typename Type>
	inline Matrix<Type> ConstructOrthoMatrix(Type w, Type h, Type n, Type f) {
		return ConstructOrthoMatrix(-w / 2, w / 2, -h / 2, h / 2, n, f);
	}

	template<typename Type>
	inline Matrix<Type> ConstructViewMatrix(const Vector4<Type> &eye, const Vector4<Type> &at, const Vector4<Type> &up) {
		/*
		zaxis = normal(At - Eye)
		xaxis = normal(cross(Up, zaxis))
		yaxis = cross(zaxis, xaxis)

		xaxis.x           yaxis.x           zaxis.x          0
		xaxis.y           yaxis.y           zaxis.y          0
		xaxis.z           yaxis.z           zaxis.z          0
		-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
		*/

		Vector4<Type> zDir = (at - eye).Normalize();
		Vector4<Type> xDir = up.Cross(zDir).Normalize();
		Vector4<Type> yDir = zDir.Cross(xDir).Normalize();

		xDir.w = yDir.w = zDir.w = 0;	// vector

		return Matrix<Type>(xDir.x, yDir.x, zDir.x, 0,
			xDir.y, yDir.y, zDir.y, 0,
			xDir.z, yDir.z, zDir.z, 0,
			-xDir.Dot(eye), -yDir.Dot(eye), -zDir.Dot(eye), 1);
	}
#endif // USING_GLM

}

#ifdef USING_GLM
namespace KY
{
	namespace mat4x4_utils
	{
		extern glm::mat4x4 INDENTIFY;
		extern glm::mat4x4 ZERO;
	}
}
#endif // USING_GLM
#endif // _MATRIX_H_