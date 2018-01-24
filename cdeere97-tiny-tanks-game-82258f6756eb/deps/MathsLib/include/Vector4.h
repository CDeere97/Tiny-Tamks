////////////////////////////////////////////////////////////
// File: Vector4.h
// Author: Chris Deere
// Date Created: 07/03/17
// Brief: Vector 4 header file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#ifndef _VECTOR4_H_
#define _VECTOR4_H_

class Vector4
{
public:
	// Constructors to initialise values
	Vector4();
	Vector4(float a_x, float a_y, float a_z, float a_w);
	Vector4(const Vector4& a_v4);

	// Getter
	void getPos(float& a_x, float& a_y, float& a_z, float& a_w) const;
	//Setter
	void setPos(const float a_x, const float a_y, const float a_z, const float a_w);

	~Vector4();

	// Functions
	Vector4		operator +		(const Vector4& a_v4) const;
	Vector4&	operator +=		(const Vector4& a_v4);
	Vector4		operator -		(const Vector4& a_v4) const;
	Vector4&	operator -=		(const Vector4& a_v4);
	Vector4		operator *		(const Vector4& a_v4) const;
	Vector4&	operator *=		(const Vector4& a_v4);
	Vector4		operator /		(const Vector4& a_v4) const;
	Vector4&	operator /=		(const Vector4& a_v4);
	bool		operator ==		(const Vector4& a_v4) const;
	bool		operator !=		(const Vector4& a_v4) const;
	float		magnitude();
	float		magnitudeSquared();
	float		distanceBetweenVectors(Vector4 &a_v4a, Vector4 &a_v4b);
	float		distanceBetweenVectorsSquared(Vector4 &a_v4a, Vector4 &a_v4b);
	void		normalise();
	float		dotProduct(Vector4 &a_v4a, Vector4 &a_v4b);
	float		crossProduct(Vector4 &a_v4a, Vector4 &a_v4b);

	// The vector's x, y and z values
	
	float x;
	float y;
	float z;
	float w;
};
#endif

