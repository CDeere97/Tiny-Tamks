////////////////////////////////////////////////////////////
// File: Matrix4.cpp
// Author: Chris Deere
// Date Created: 06/04/17
// Brief: Matrix 4 file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#include "Matrix4.h"
#include <cmath> // Can use sin and cos functions for rotation

Matrix4::Matrix4()
{
	m_11 = 0.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
	m_21 = 0.f, m_22 = 0.f, m_23 = 0.f; m_24 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f; m_34 = 0.f;
	m_41 = 0.f, m_42 = 0.f, m_43 = 0.f; m_44 = 0.f;
}

Matrix4::Matrix4(float a_11, float a_12, float a_13, float a_14, float a_21, float a_22, float a_23, float a_24, float a_31, float a_32, float a_33, float a_34, float a_41, float a_42, float a_43, float a_44)
{
	m_11 = a_11; m_12 = a_12; m_13 = a_13; m_14 = a_14;
	m_21 = a_21; m_22 = a_22; m_23 = a_23; m_24 = a_24;
	m_31 = a_31; m_32 = a_32; m_33 = a_33; m_34 = a_34;
	m_41 = a_41; m_42 = a_42; m_43 = a_43; m_44 = a_44;
}

Matrix4::Matrix4(const Matrix4 & a_m4)
{
	m_11 = a_m4.m_11; m_12 = a_m4.m_12; m_13 = a_m4.m_13; m_14 = a_m4.m_14;
	m_21 = a_m4.m_21; m_22 = a_m4.m_22; m_23 = a_m4.m_23; m_24 = a_m4.m_24;
	m_31 = a_m4.m_31; m_32 = a_m4.m_32; m_33 = a_m4.m_33; m_34 = a_m4.m_34;
	m_41 = a_m4.m_41; m_42 = a_m4.m_42; m_43 = a_m4.m_43; m_44 = a_m4.m_44;
}

Matrix4::~Matrix4()
{
}

const Matrix4 Matrix4::IDENTITY = Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
										  0.0f, 1.0f, 0.0f, 0.0f,
										  0.0f, 0.0f, 1.0f, 0.0f,
										  0.0f, 0.0f, 0.0f, 1.0f);

void Matrix4::GetRow(int a_rowNumber, Vector4 & a_row) const
{
	a_row.x = m[a_rowNumber][0];
	a_row.y = m[a_rowNumber][1];
	a_row.z = m[a_rowNumber][2];
	a_row.w = m[a_rowNumber][3];
}

void Matrix4::SetRow(int a_rowNumber, const Vector4 & a_row)
{
	m[a_rowNumber][0] = a_row.x;
	m[a_rowNumber][1] = a_row.y;
	m[a_rowNumber][2] = a_row.z;
	m[a_rowNumber][3] = a_row.w;
}

Matrix4 Matrix4::operator+(const Matrix4 & a_m4) const
{
	Matrix4 returnMatrix;

	returnMatrix.m_11 = m_11 + a_m4.m_11, returnMatrix.m_12 = m_12 + a_m4.m_12, returnMatrix.m_13 = m_13 + a_m4.m_13, returnMatrix.m_14 = m_14 + a_m4.m_14;
	returnMatrix.m_21 = m_21 + a_m4.m_21, returnMatrix.m_22 = m_22 + a_m4.m_22, returnMatrix.m_23 = m_23 + a_m4.m_23, returnMatrix.m_24 = m_24 + a_m4.m_24;
	returnMatrix.m_31 = m_31 + a_m4.m_31, returnMatrix.m_32 = m_32 + a_m4.m_32, returnMatrix.m_33 = m_33 + a_m4.m_33, returnMatrix.m_34 = m_34 + a_m4.m_34;
	returnMatrix.m_41 = m_41 + a_m4.m_41, returnMatrix.m_42 = m_42 + a_m4.m_42, returnMatrix.m_43 = m_43 + a_m4.m_43, returnMatrix.m_44 = m_44 + a_m4.m_44;

	return returnMatrix;
}

Matrix4 Matrix4::operator-(const Matrix4 & a_m4) const
{
	Matrix4 returnMatrix;

	returnMatrix.m_11 = m_11 - a_m4.m_11, returnMatrix.m_12 = m_12 - a_m4.m_12, returnMatrix.m_13 = m_13 - a_m4.m_13, returnMatrix.m_14 = m_14 - a_m4.m_14;
	returnMatrix.m_21 = m_21 - a_m4.m_21, returnMatrix.m_22 = m_22 - a_m4.m_22, returnMatrix.m_23 = m_23 - a_m4.m_23, returnMatrix.m_24 = m_24 - a_m4.m_24;
	returnMatrix.m_31 = m_31 - a_m4.m_31, returnMatrix.m_32 = m_32 - a_m4.m_32, returnMatrix.m_33 = m_33 - a_m4.m_33, returnMatrix.m_34 = m_34 - a_m4.m_34;
	returnMatrix.m_41 = m_41 - a_m4.m_41, returnMatrix.m_42 = m_42 - a_m4.m_42, returnMatrix.m_43 = m_43 - a_m4.m_43, returnMatrix.m_44 = m_44 - a_m4.m_44;

	return returnMatrix;
}

float Matrix4::Determinant_3() const
{
	return (m_11 * (m_22 * m_33 - m_23 * m_22) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31));
}

float Matrix4::Recipf(float const invert)
{
	return 1 / invert;
}

bool Matrix4::Invert()
{
	float fDeterminant = Determinant_3();
	if (fDeterminant != 0.0f)
	{
		const float	fInvDet = Recipf(fDeterminant);

		Matrix4 mat = *this;
		m_11 = (mat.m_22 * mat.m_33 - mat.m_23 * mat.m_32) * fInvDet;
		m_12 = (mat.m_13 * mat.m_32 - mat.m_12 * mat.m_33) * fInvDet;
		m_13 = (mat.m_12 * mat.m_23 - mat.m_13 * mat.m_22) * fInvDet;
		m_14 = 0.0f;

		m_21 = (mat.m_23 * mat.m_31 - mat.m_21 * mat.m_33) * fInvDet;
		m_22 = (mat.m_11 * mat.m_33 - mat.m_13 * mat.m_31) * fInvDet;
		m_23 = (mat.m_13 * mat.m_21 - mat.m_11 * mat.m_23) * fInvDet;
		m_24 = 0.0f;

		m_31 = (mat.m_21 * mat.m_32 - mat.m_22 * mat.m_31) * fInvDet;
		m_32 = (mat.m_12 * mat.m_31 - mat.m_11 * mat.m_32) * fInvDet;
		m_33 = (mat.m_11 * mat.m_22 - mat.m_12 * mat.m_21) * fInvDet;
		m_34 = 0.0f;

		m_41 = (mat.m_21 * (mat.m_33 * mat.m_42 - mat.m_32 * mat.m_43) +
				mat.m_22 * (mat.m_31 * mat.m_43 - mat.m_33 * mat.m_41) +
				mat.m_23 * (mat.m_32 * mat.m_41 - mat.m_31 * mat.m_42)) * fInvDet;
		m_42 = (mat.m_11 * (mat.m_32 * mat.m_43 - mat.m_33 * mat.m_42) +
				mat.m_12 * (mat.m_33 * mat.m_41 - mat.m_31 * mat.m_43) +
				mat.m_13 * (mat.m_31 * mat.m_42 - mat.m_32 * mat.m_41)) * fInvDet;
		m_42 = (mat.m_11 * (mat.m_23 * mat.m_42 - mat.m_22 * mat.m_43) +
				mat.m_12 * (mat.m_21 * mat.m_43 - mat.m_23 * mat.m_41) +
				mat.m_13 * (mat.m_22 * mat.m_41 - mat.m_21 * mat.m_42)) * fInvDet;
		m_44 = 1.0f;

		return true;
	}
	else
	{
		return false;
	}
}

float Matrix4::Transpose()
{
	
	float transM[4][4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			transM[j][i] = m[i][j];
		}
	}

	return transM[0][0];
}

float Matrix4::Translate()
{
	float returnMatrix;

	float temp = m_12, m_12 = m_21, m_21 = temp;
	temp = m_13, m_13 = m_31, m_31 = temp;
	temp = m_14, m_14 = m_41, m_41 = temp;
	temp = m_23, m_23 = m_32, m_32 = temp;
	temp = m_24, m_24 = m_42, m_42 = temp;
	temp = m_34, m_34 = m_43, m_42 = temp;
	
	return returnMatrix;
}

Matrix4 Matrix4::operator*(const float & a_scalar) const
{
	return Matrix4(m_11 * a_scalar, m_12 * a_scalar, m_13 * a_scalar, m_14 * a_scalar,
				   m_21 * a_scalar, m_22 * a_scalar, m_23 * a_scalar, m_24 * a_scalar,
				   m_31 * a_scalar, m_32 * a_scalar, m_33 * a_scalar, m_34 * a_scalar,
				   m_41 * a_scalar, m_42 * a_scalar, m_43 * a_scalar, m_44 * a_scalar);
}

Matrix4 Matrix4::operator*(const Matrix4 & a_m4) const
{
	Matrix4 returnMatrix;

	returnMatrix.m_11 = (m_11 * a_m4.m_11) + (m_12 * a_m4.m_21) + (m_13 * a_m4.m_31) + (m_14 * a_m4.m_41);
	returnMatrix.m_12 = (m_11 * a_m4.m_12) + (m_12 * a_m4.m_22) + (m_13 * a_m4.m_32) + (m_14 * a_m4.m_42);
	returnMatrix.m_13 = (m_11 * a_m4.m_13) + (m_12 * a_m4.m_23) + (m_13 * a_m4.m_33) + (m_14 * a_m4.m_43);
	returnMatrix.m_14 = (m_11 * a_m4.m_14) + (m_12 * a_m4.m_24) + (m_13 * a_m4.m_34) + (m_14 * a_m4.m_44);

	returnMatrix.m_21 = (m_21 * a_m4.m_11) + (m_22 * a_m4.m_21) + (m_23 * a_m4.m_31) + (m_24 * a_m4.m_41);
	returnMatrix.m_22 = (m_21 * a_m4.m_12) + (m_22 * a_m4.m_22) + (m_23 * a_m4.m_32) + (m_24 * a_m4.m_42);
	returnMatrix.m_23 = (m_21 * a_m4.m_13) + (m_22 * a_m4.m_23) + (m_23 * a_m4.m_33) + (m_24 * a_m4.m_43);
	returnMatrix.m_24 = (m_21 * a_m4.m_14) + (m_22 * a_m4.m_24) + (m_23 * a_m4.m_34) + (m_24 * a_m4.m_44);

	returnMatrix.m_31 = (m_31 * a_m4.m_11) + (m_32 * a_m4.m_21) + (m_33 * a_m4.m_31) + (m_34 * a_m4.m_41);
	returnMatrix.m_32 = (m_31 * a_m4.m_12) + (m_32 * a_m4.m_22) + (m_33 * a_m4.m_32) + (m_34 * a_m4.m_42);
	returnMatrix.m_33 = (m_31 * a_m4.m_13) + (m_32 * a_m4.m_23) + (m_33 * a_m4.m_33) + (m_34 * a_m4.m_43);
	returnMatrix.m_34 = (m_31 * a_m4.m_14) + (m_32 * a_m4.m_24) + (m_33 * a_m4.m_34) + (m_34 * a_m4.m_44);

	returnMatrix.m_41 = (m_41 * a_m4.m_11) + (m_42 * a_m4.m_21) + (m_43 * a_m4.m_31) + (m_34 * a_m4.m_41);
	returnMatrix.m_42 = (m_41 * a_m4.m_12) + (m_42 * a_m4.m_22) + (m_43 * a_m4.m_32) + (m_34 * a_m4.m_42);
	returnMatrix.m_43 = (m_41 * a_m4.m_13) + (m_42 * a_m4.m_23) + (m_43 * a_m4.m_33) + (m_34 * a_m4.m_43);
	returnMatrix.m_44 = (m_41 * a_m4.m_14) + (m_42 * a_m4.m_24) + (m_43 * a_m4.m_34) + (m_34 * a_m4.m_44);

	return  returnMatrix;
}

bool Matrix4::operator==(const Matrix4 & a_m4) const
{
	return m_11 == a_m4.m_11 && m_12 == a_m4.m_12 && m_13 == a_m4.m_13 && m_14 == a_m4.m_14 &&
		m_21 == a_m4.m_21 && m_22 == a_m4.m_22 && m_23 == a_m4.m_23 && m_24 == a_m4.m_24 &&
		m_31 == a_m4.m_31 && m_32 == a_m4.m_32 && m_33 == a_m4.m_33 && m_34 == a_m4.m_34 &&
		m_41 == a_m4.m_41 && m_32 == a_m4.m_42 && m_43 == a_m4.m_43 && m_44 == a_m4.m_44;
}

bool Matrix4::operator!=(const Matrix4 & a_m4) const
{
	return m_11 != a_m4.m_11 || m_12 != a_m4.m_12 || m_13 != a_m4.m_13 || m_14 != a_m4.m_14 ||
		m_21 != a_m4.m_21 || m_22 != a_m4.m_22 || m_23 != a_m4.m_23 || m_24 != a_m4.m_24 ||
		m_31 != a_m4.m_31 || m_32 != a_m4.m_32 || m_33 != a_m4.m_33 || m_34 != a_m4.m_34 ||
		m_41 != a_m4.m_41 || m_42 != a_m4.m_42 || m_43 != a_m4.m_43 || m_44 != a_m4.m_44;
}

void Matrix4::RotateX(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f; m_14 = 0.0f;
	m_21 = 0.0f; m_22 = co; m_23 = si; m_24 = 0.0f;
	m_31 = 0.0f; m_32 = -si; m_33 = co; m_34 = 0.0f;
	m_41 = 0.0f; m_42 = 0.0f; m_33 = 0.0f; m_34 = 1.0f;
}

void Matrix4::RotateY(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = co; m_12 = 0.0f; m_13 = -si; m_14 = 0.0f;
	m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f; m_24 = 0.0f;
	m_31 = si; m_32 = 0.0f; m_33 = co; m_34 = 0.0f;
	m_41 = 0.0f; m_42 = 0.0f; m_43 = 0.0f; m_44 = 1.0f;
}

void Matrix4::RotateZ(float fAngle)
{
	const float co = cosf(fAngle);
	const float si = sinf(fAngle);

	m_11 = co; m_12 = si; m_13 = 0.0f; m_14 = 0.0f;
	m_21 = -si; m_22 = co; m_23 = 0.0f; m_24 = 0.0f;
	m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f; m_24 = 0.0f;
	m_41 = 0.0f; m_42 = 0.0f; m_43 = 0.0f; m_44 = 1.0f;
}

Matrix4::operator float *()
{
	return static_cast<float*>(i);
}

Matrix4 ::operator const float *()
{
	return const_cast<float*>(i);
}