////////////////////////////////////////////////////////////
// File: Matrix3.cpp
// Author: Chris Deere
// Date Created: 23/03/17
// Brief: Matrix 3 file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#include "Matrix3.h"
#include <cmath> // Can use sin and cos functions for rotation

Matrix3::Matrix3()
{
	m_11 = 0.0f, m_12 = 0.0f, m_13 = 0.0f;
	m_21 = 0.0f, m_22 = 0.0f, m_23 = 0.0f;
	m_31 = 0.0f, m_32 = 0.0f, m_33 = 0.0f;
}

Matrix3::Matrix3(float a_11, float a_12, float a_13, float a_21, float a_22, float a_23, float a_31, float a_32, float a_33)
{
	m_11 = a_11; m_12 = a_12; m_13 = a_13;
	m_21 = a_21; m_22 = a_22; m_23 = a_23;
	m_31 = a_31; m_32 = a_32; m_33 = a_33;
}

Matrix3::Matrix3(const Matrix3 & a_m3)
{
	m_11 = a_m3.m_11; m_12 = a_m3.m_12; m_13 = a_m3.m_13;
	m_21 = a_m3.m_21; m_22 = a_m3.m_22; m_23 = a_m3.m_23;
	m_31 = a_m3.m_31; m_32 = a_m3.m_32; m_33 = a_m3.m_33;
}

Matrix3::~Matrix3()
{
}

const Matrix3 Matrix3::IDENTITY = Matrix3(1.0f, 0.0f, 0.0f,
	                                      0.0f, 1.0f, 0.0f,
	                                      0.0f, 0.0f, 1.0f);

void Matrix3::GetRow(int a_rowNumber, Vector3 & a_row) const
{
	a_row.x = m[a_rowNumber][0];
	a_row.y = m[a_rowNumber][1];
	a_row.z = m[a_rowNumber][2];
}

void Matrix3::SetRow(int a_rowNumber, const Vector3 & a_row)
{
	m[a_rowNumber][0] = a_row.x;
	m[a_rowNumber][1] = a_row.y;
	m[a_rowNumber][2] = a_row.z;
}

Matrix3 Matrix3::operator+(const Matrix3 & a_m3) const
{
	Matrix3 returnMatrix;

	returnMatrix.m_11 = m_11 + a_m3.m_11, returnMatrix.m_12 = m_12 + a_m3.m_12, returnMatrix.m_13 = m_13 + a_m3.m_13;
	returnMatrix.m_21 = m_21 + a_m3.m_21, returnMatrix.m_22 = m_22 + a_m3.m_22, returnMatrix.m_23 = m_23 + a_m3.m_23;
	returnMatrix.m_31 = m_31 + a_m3.m_31, returnMatrix.m_32 = m_32 + a_m3.m_32, returnMatrix.m_33 = m_33 + a_m3.m_33;

	return returnMatrix;
}

Matrix3 Matrix3::operator-(const Matrix3 & a_m3) const
{
	Matrix3 returnMatrix;

	returnMatrix.m_11 = m_11 - a_m3.m_11, returnMatrix.m_12 = m_12 - a_m3.m_12, returnMatrix.m_13 = m_13 - a_m3.m_13;
	returnMatrix.m_21 = m_21 - a_m3.m_21, returnMatrix.m_22 = m_22 - a_m3.m_22, returnMatrix.m_23 = m_23 - a_m3.m_23;
	returnMatrix.m_31 = m_31 - a_m3.m_31, returnMatrix.m_32 = m_32 - a_m3.m_32, returnMatrix.m_33 = m_33 - a_m3.m_33;

	return returnMatrix;
}



Matrix3 Matrix3::operator*(const float & a_scalar) const
{
	return Matrix3(m_11 * a_scalar, m_12 * a_scalar, m_13 * a_scalar,
				   m_21 * a_scalar, m_22 * a_scalar, m_23 * a_scalar,
	               m_31 * a_scalar, m_32 * a_scalar, m_33 * a_scalar);
}

Matrix3 Matrix3::operator*(const Matrix3 & a_m3) const
{
	Matrix3 returnMatrix;

	returnMatrix.m_11 = (m_11 * a_m3.m_11) + (m_12 * a_m3.m_21) + (m_13 * a_m3.m_31);
	returnMatrix.m_12 = (m_11 * a_m3.m_12) + (m_12 * a_m3.m_22) + (m_13 * a_m3.m_32);
	returnMatrix.m_13 = (m_11 * a_m3.m_13) + (m_12 * a_m3.m_23) + (m_13 * a_m3.m_33);

	returnMatrix.m_21 = (m_21 * a_m3.m_11) + (m_22 * a_m3.m_21) + (m_23 * a_m3.m_31);
	returnMatrix.m_22 = (m_21 * a_m3.m_12) + (m_22 * a_m3.m_22) + (m_23 * a_m3.m_32);
	returnMatrix.m_23 = (m_21 * a_m3.m_13) + (m_22 * a_m3.m_23) + (m_23 * a_m3.m_33);

	returnMatrix.m_31 = (m_31 * a_m3.m_11) + (m_32 * a_m3.m_21) + (m_33 * a_m3.m_31);
	returnMatrix.m_32 = (m_31 * a_m3.m_12) + (m_32 * a_m3.m_22) + (m_33 * a_m3.m_32);
	returnMatrix.m_33 = (m_31 * a_m3.m_13) + (m_32 * a_m3.m_23) + (m_33 * a_m3.m_33);
	
	
	return  returnMatrix;
}

bool Matrix3::operator==(const Matrix3 & a_m3) const
{
	return m_11 == a_m3.m_11 && m_12 == a_m3.m_12 && m_13 == a_m3.m_13 &&
		m_21 == a_m3.m_21 && m_22 == a_m3.m_22 && m_23 == a_m3.m_23 &&
		m_31 == a_m3.m_31 && m_32 == a_m3.m_32 && m_33 == a_m3.m_33;
	
}

bool Matrix3::operator!=(const Matrix3 & a_m3) const
{
	return m_11 != a_m3.m_11 || m_12 != a_m3.m_12 || m_13 != a_m3.m_13 ||
		m_21 != a_m3.m_21 || m_22 != a_m3.m_22 || m_23 != a_m3.m_23 ||
		m_31 != a_m3.m_31 || m_32 != a_m3.m_32 || m_33 != a_m3.m_33;
}

float Matrix3::Determinant() const
{
	return (m_11 * (m_22 * m_33 - m_23 * m_22) +
		m_12 * (m_23 * m_31 - m_21 * m_33) +
		m_13 * (m_21 * m_32 - m_22 * m_31));
}

float Matrix3::Recipf(float const invert)
{
	return 1 / invert;
}

bool Matrix3::Invert()
{
	float fDeterminant = Determinant();
	if (fDeterminant != 0.0f)
	{
		const float	fInvDet = Recipf(fDeterminant);

		Matrix3 mat = *this;
		m_11 = (mat.m_22 * mat.m_33 - mat.m_23 * mat.m_32) * fInvDet;
		m_12 = (mat.m_13 * mat.m_32 - mat.m_12 * mat.m_33) * fInvDet;
		m_13 = (mat.m_12 * mat.m_23 - mat.m_13 * mat.m_22) * fInvDet;

		m_21 = (mat.m_23 * mat.m_31 - mat.m_21 * mat.m_33) * fInvDet;
		m_22 = (mat.m_11 * mat.m_33 - mat.m_13 * mat.m_31) * fInvDet;
		m_23 = (mat.m_13 * mat.m_21 - mat.m_11 * mat.m_23) * fInvDet;

		m_31 = (mat.m_21 * mat.m_32 - mat.m_22 * mat.m_31) * fInvDet;
		m_32 = (mat.m_12 * mat.m_31 - mat.m_11 * mat.m_32) * fInvDet;
		m_33 = (mat.m_11 * mat.m_22 - mat.m_12 * mat.m_21) * fInvDet;

		return true;
	}
	return false;
}

float Matrix3::Transpose()
{
	float transM[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			transM[j][i] = m[i][j];
		}
	}

	return transM[0][0];
}

void Matrix3::Translate(Vector2 aNewPosition)
{
	m_11 = 1.0f; m_12 = 0.0f; m_13 = aNewPosition.x;
	m_21 = 0.0f; m_22 = 1.0f; m_23 = aNewPosition.y;
	m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f;

}

void Matrix3::RotateX(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f;
	m_21 = 0.0f; m_22 = co; m_23 = si;
	m_31 = 0.0f; m_32 = -si; m_33 = co;    
}

void Matrix3::RotateY(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = co; m_12 = 0.0f; m_13 = -si;
	m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f;
	m_31 = si; m_32 = 0.0f; m_33 = co;
}

void Matrix3::RotateZ(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = co; m_12 = si; m_13 = 0.0f;
	m_21 = -si; m_22 = co; m_23 = 0.0f;
	m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f;
}

Vector3 operator*(const Vector3 & a_v3, const Matrix3 & a_m3)
{
	return Vector3(
		a_v3.x * a_m3.m_11 + a_v3.y * a_m3.m_21 + a_v3.z * a_m3.m_31,
		a_v3.x * a_m3.m_21 + a_v3.y * a_m3.m_22 + a_v3.z * a_m3.m_32, 
		a_v3.x * a_m3.m_31 + a_v3.y * a_m3.m_32 + a_v3.z * a_m3.m_33);
}


