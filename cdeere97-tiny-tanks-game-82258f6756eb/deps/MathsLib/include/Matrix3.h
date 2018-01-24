////////////////////////////////////////////////////////////
// File: Matrix3.h
// Author: Chris Deere
// Date Created: 23/03/17
// Brief: Matrix 3 header file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "Vector2.h"
#include "Vector3.h"

class Matrix3
{
public:
	// Constructors to initialise values
	Matrix3();
	Matrix3(float m_11, float m_12, float m_13, float m_21, float m_22, float m_23, float m_31, float m_32, float m_33);
	Matrix3(const Matrix3& a_m3);
	~Matrix3();
	static const Matrix3 IDENTITY;

	union
	{
		float m[3][3];
		struct
		{
			float m_11, m_12, m_13;
			float m_21, m_22, m_23;
			float m_31, m_32, m_33;
		};
	};

	// Functions
	
	void GetRow(int a_rowNumber, Vector3& a_row) const; // Getter
	void SetRow(int a_rowNumber, const Vector3& a_row); // Setter

	//Operations
	Matrix3		operator +		(const Matrix3& a_m3) const; // Addition
	Matrix3		operator -		(const Matrix3& a_m3) const;// Subtraction
	Matrix3		operator *		(const float& a_scalar) const; // Multiply by a scalar 
	Matrix3		operator *		(const Matrix3& a_m3) const; // Multiply by a vector 
	friend Vector3 operator*(const Vector3& a_v3, const Matrix3& a_m3);
	
	bool		operator ==		(const Matrix3& a_m3) const; // Equals to
	bool		operator !=		(const Matrix3& a_m3) const;// Not equals to

	
	float Determinant() const; // Function to find the determinant to be used in inversion
	float Recipf(float const invert); // Function to find the reciprocal  to be used in inversion
	bool Invert(); // Inversion 
	float Transpose(); // Transposition


	void Translate(Vector2 aNewPosition); // Translation
	// Scale
	// Rotation
	void RotateX(float fAngle);
	void RotateY(float fAngle);
	void RotateZ(float fAngle);

};
#endif