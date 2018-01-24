////////////////////////////////////////////////////////////
// File: Vector2.cpp
// Author: Chris Deere
// Date Created: 01/03/17
// Brief: Vector 2 file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#include "Vector2.h"
#include <cmath>


Vector2::Vector2() // Initialises x and y values to 0 
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float a_x, float a_y) // Initialises x and y to custom values
{
	x = a_x;
	y = a_y;
}

Vector2::Vector2(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}

void Vector2::getPos(float& a_x, float& a_y) const // Gets the values
{
	a_x = x;
	a_y = y;
}

void Vector2::setPos(const float a_x, const float a_y) // Sets the values
{
	x = a_x;
	y = a_y;
}

Vector2::~Vector2() // Destructor
{
}

Vector2 Vector2::operator +(const Vector2& a_v2) const // Addition operator
{
	return Vector2(x + a_v2.x, y + a_v2.y);
}

Vector2& Vector2::operator +=(const Vector2& a_v2) // Addition operator overload
{
	x += a_v2.x;
	y += a_v2.y;
	return *this;
}

Vector2 Vector2::operator -(const Vector2& a_v2) const // Subtraction operator
{
	return Vector2(x - a_v2.x, y - a_v2.y);
}

Vector2& Vector2::operator -=(const Vector2& a_v2) // Subtraction operator overload
{
	x -= a_v2.x;
	y -= a_v2.y;
	return *this;
}

Vector2 Vector2::operator *(const Vector2& a_v2) const // Multiplication operator
{
	return Vector2(x * a_v2.x, y * a_v2.y);
}

Vector2& Vector2::operator *=(const Vector2& a_v2) // Multiplication operator overload
{
	x *= a_v2.x;
	y *= a_v2.y;
	return *this;
}

Vector2 Vector2::operator /(const Vector2& a_v2) const // Division operator
{
	return Vector2(x / a_v2.x, y / a_v2.y);
}

Vector2& Vector2::operator /=(const Vector2& a_v2) // Division operator overload
{
	x /= a_v2.x;
	y /= a_v2.y;
	return *this;
}


bool Vector2::operator ==(const Vector2& a_v2) const // Equal to operator
{
	return (x == a_v2.x && y == a_v2.y);
}

bool Vector2::operator !=(const Vector2& a_v2) const // Not equal to operator
{
	return (x != a_v2.x || y != a_v2.y);
}

float Vector2::magnitude() // Magnitude of the vector
{
	return sqrt(x*x + y*y);
}

float Vector2::magnitudeSquared() // Squared magnitude of the vector
{
	return x*x + y*y;
}

float Vector2::distanceBetweenVectors(Vector2 &a_v2) // Distance between the vectors
{
	Vector2 temp = *this - a_v2;
	return sqrtf(temp.x * temp.x + temp.y * y);
}

float Vector2::distanceBetweenVectorsSquared(Vector2 & a_v2) // Squared Distance between the two vectors
{
	Vector2 temp = *this - a_v2;
	return temp.x * temp.x + temp.y * y;
}

void Vector2::normalise() // Normalises the vectors
{
	float length = magnitude();

	x = x / length;
	y = y / length;

}

float Vector2::dotProduct(Vector2 & a_v2a, Vector2 & a_v2b) // Dot product between the vectors
{
	return (a_v2a.x * a_v2b.x) + (a_v2a.y * a_v2b.y);
}

Vector2 Vector2::getPerpendicular() // Gets the perpendicular of the vectors (2D Cross Product)
{
	return Vector2(-y, x);
}

Vector2::operator float*()
{
	return static_cast<float*>(&x);
}

Vector2::operator const float*() const
{
	return const_cast<float*>(&x);
}





