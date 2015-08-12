#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector4.h"

namespace KY
{
	// row major
	template<typename Type>
    class Matrix
    {
	public:
		union{
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
		Matrix(){}
		Matrix( float _m00, float _m01, float _m02, float _m03,
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

		~Matrix(){}

		VecType& Row(uint32 rowIdx){
			return *(reinterpret_cast<VecType*>(this) + rowIdx);
		}

		const VecType& Row(uint32 rowIdx) const{
			return *(reinterpret_cast<const VecType*>(this) + rowIdx);
		}

		VecType Col(uint32 colIdx) const{
			return VecType(mm[0][colIdx], mm[1][colIdx], mm[2][colIdx], mm[3][colIdx]);
		}

		void Inverse(){

		}

		Matrix<Type> ToInverse() const{

		}

		Type Det(){

		}

		void Transpose(){

		}

		Matrix<Type> ToTranspose() const{

		}

	public:
		static Matrix INDENTIFY;
		static Matrix ZERO;
    };

	typedef Matrix<float> Mat4x4F;

	template<typename Type>
	inline 	Vector4<Type> operator*(const Matrix<Type>& mat, const Vector4<Type>& v) {
		// not effective
		return Vector4<Type>(mat.Col(0).Dot(v), mat.Col(1).Dot(v), mat.Col(2).Dot(v), mat.Col(3).Dot(v));
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
	inline Matrix<Type> ConstructPrespectiveMatrix(Type l, Type r, Type b, Type t, Type n, Type f){
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
	inline Matrix<Type> ConstructPrespectiveMatrix(Type fov /*= 1.570795f*/, Type aspect /*= 1.0f*/, float n /*= 1.0f*/, float f /*= 1000.0f*/){
		const Type height = Type(std::tan(fov / 2));
		const Type width = aspect * height;

		return ConstructPrespectiveMatrix(-width, width, -height, height, n, f);
	}

	template<typename Type>
	inline Matrix<Type> ConstructOrthoMatrix(Type l, Type r, Type b, Type t, Type n, Type f){
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
	inline Matrix<Type> ConstructOrthoMatrix(Type w, Type h, Type n, Type f){
		return ConstructOrthoMatrix(-w / 2, w / 2, -h / 2, h / 2, n, f);
	}

	template<typename Type>
	inline Matrix<Type> ConstructViewMatrix(const Vector4<Type> &eye, const Vector4<Type> &at, const Vector4<Type> &up){
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
}
#endif // _MATRIX_H_