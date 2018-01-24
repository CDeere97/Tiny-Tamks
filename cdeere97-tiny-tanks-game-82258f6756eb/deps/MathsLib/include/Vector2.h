////////////////////////////////////////////////////////////
// File: Vector2.h
// Author: Chris Deere
// Date Created: 01/03/17
// Brief: Vector 2 header file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	// Constructors to initialise values
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& a_v2);
	
	// Getter
	void getPos(float& a_x, float& a_y) const;
	//Setter
	void setPos(const float a_x, const float a_y);
	
	~Vector2();

	// Functions
	Vector2		operator +		(const Vector2& a_v2) const;
	Vector2&	operator +=		(const Vector2& a_v2);
	Vector2		operator -		(const Vector2& a_v2) const;
	Vector2&	operator -=		(const Vector2& a_v2);
	Vector2		operator *		(const Vector2& a_v2) const;
	Vector2&	operator *=		(const Vector2& a_v2);
	Vector2		operator /		(const Vector2& a_v2) const;
	Vector2&	operator /=		(const Vector2& a_v2);
	bool		operator ==		(const Vector2& a_v2) const;
	bool		operator !=		(const Vector2& a_v2) const;
	float		magnitude();
	float		magnitudeSquared();
	float		distanceBetweenVectors(Vector2 &a_v2);
	float		distanceBetweenVectorsSquared(Vector2 &a_v2);
	void		normalise();
	float		dotProduct(Vector2 &a_v2a, Vector2 &a_v2b);
	Vector2		getPerpendicular();

	operator float*();
	operator const float*() const;

	// The vector's x and y values
	float x;
	float y;
};
#endif
