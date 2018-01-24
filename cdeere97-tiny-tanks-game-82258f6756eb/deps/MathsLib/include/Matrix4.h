////////////////////////////////////////////////////////////
// File: Matrix4.h
// Author: Chris Deere
// Date Created: 06/04/17
// Brief: Matrix 4 header file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
class Matrix4
{
public:
	// Constructors to initialise values
	Matrix4();
	Matrix4(float m_11, float m_12, float m_13, float m_14, float m_21, float m_22, float m_23, float m_24, float m_31, float m_32, float m_33, float m_34, float m_41, float m_42, float m_43, float m_44);
	Matrix4(const Matrix4& a_m4);
	~Matrix4();
	static const Matrix4 IDENTITY;

	union
	{
		struct {
			
			float m[4][4];
		};
		struct
		{
			float m_11, m_12, m_13, m_14;
			float m_21, m_22, m_23, m_24;
			float m_31, m_32, m_33, m_34;
			float m_41, m_42, m_43, m_44;
		};

		struct
		{
			float i[16];
		};
	};

	// Functions
	void GetRow(int a_rowNumber, Vector4& a_row) const;
	void SetRow(int a_rowNumber, const Vector4& a_row);

	Matrix4		operator +		(const Matrix4& a_m4) const;
	Matrix4		operator -		(const Matrix4& a_m4) const;

	float Determinant_3() const;
	float Recipf(float const invert);
	bool Invert();
	float Transpose();
	float Translate();

	Matrix4		operator *		(const float& a_scalar) const; // Multiply by a scalar (scaling)
	Matrix4		operator *		(const Matrix4& a_m4) const; // Multiply by a vector 

	bool		operator ==		(const Matrix4& a_m4) const;
	bool		operator !=		(const Matrix4& a_m4) const;

	//Rotation
	void RotateX(float fAngle);
	void RotateY(float fAngle);
	void RotateZ(float fAngle);

	operator float*();
	operator const float*();
};
#endif
