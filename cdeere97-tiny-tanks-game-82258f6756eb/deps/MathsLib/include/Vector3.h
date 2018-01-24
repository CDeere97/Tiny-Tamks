////////////////////////////////////////////////////////////
// File: Vector3.h
// Author: Chris Deere
// Date Created: 06/03/17
// Brief: Vector 3 header file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
	// Constructors to initialise values
	Vector3();
	Vector3(float a_x, float a_y, float a_z);
	Vector3(const Vector3& a_v3);

	// Getter
	void getPos(float& a_x, float& a_y, float a_z) const;
	//Setter
	void setPos(const float a_x, const float a_y, const float a_z);
	
	~Vector3();
	static const Vector3 ZERO;
	static const Vector3 AXIS_Y;
	// Functions
	Vector3		operator +		(const Vector3& a_v3) const;
	Vector3&	operator +=		(const Vector3& a_v3);
	Vector3		operator -		(const Vector3& a_v3) const;
	Vector3&	operator -=		(const Vector3& a_v3);
	Vector3		operator *		(const Vector3& a_v3) const;
	Vector3&	operator *=		(const Vector3& a_v3);
	Vector3     operator *=     (const float& a_f);
	Vector3		operator /		(const Vector3& a_v3) const;
	Vector3&	operator /=		(const Vector3& a_v3);

	bool		operator ==		(const Vector3& a_v3) const;
	bool		operator !=		(const Vector3& a_v3) const;
	float		magnitude();
	float		magnitudeSquared();
	float		distanceBetweenVectors(Vector3 &a_v3a, Vector3 &a_v3b);
	float		distanceBetweenVectorsSquared(Vector3 &a_v3a, Vector3 &a_v3b);
	void		normalise();
	float		dotProduct(Vector3 &a_v3a, Vector3 &a_v3b);
	float		crossProduct(Vector3 &a_v3a, Vector3 &a_v3b);

	// The vector's x, y and z values
	float x;
	float y;
	float z;
};
#endif

