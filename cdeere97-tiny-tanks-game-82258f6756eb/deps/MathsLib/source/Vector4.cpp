////////////////////////////////////////////////////////////
// File: Vector4.cpp
// Author: Chris Deere
// Date Created: 07/03/17
// Brief: Vector 4 file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#include "Vector4.h"
#include <cmath>



Vector4::Vector4() // Initialises w, x, y and z to 0
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

Vector4::Vector4(float a_x, float a_y, float a_z, float a_w) // Initialises w, x, y and z to custom values
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	w = a_v4.w;
}

void Vector4::getPos(float& a_x, float& a_y, float& a_z, float& a_w) const // Gets the position
{
	a_x = x;
	a_y = y;
	a_z = z;
	a_w = w;
}

void Vector4::setPos(const float a_x, const float a_y, const float a_z, const float a_w) // Sets the position
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

Vector4::~Vector4()
{
}

Vector4 Vector4::operator +(const Vector4& a_v4) const // Addition operator
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}

Vector4& Vector4::operator +=(const Vector4& a_v4) // Addition operator overload
{
	x += a_v4.x;
	y += a_v4.y;
	z += a_v4.z;
	w += a_v4.w;
	return *this;
}

Vector4 Vector4::operator -(const Vector4& a_v4) const // Subtraction operator
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w - a_v4.w);
}

Vector4& Vector4::operator -=(const Vector4& a_v4) // Subtraction operator overload
{
	x -= a_v4.x;
	y -= a_v4.y;
	z -= a_v4.z;
	w -= a_v4.w;
	return *this;
}

Vector4 Vector4::operator *(const Vector4& a_v4) const // Multiplication operator
{
	return Vector4(x * a_v4.x, y * a_v4.y, z * a_v4.z, w * a_v4.w);
}

Vector4& Vector4::operator *=(const Vector4& a_v4) // Multiplication operator overload
{
	x *= a_v4.x;
	y *= a_v4.y;
	z *= a_v4.z;
	w *= a_v4.w;
	return *this;
}

Vector4 Vector4::operator /(const Vector4& a_v4) const // Division operator
{
	return Vector4(w / a_v4.w, x / a_v4.x, y / a_v4.y, z / a_v4.z);
}

Vector4& Vector4::operator /=(const Vector4& a_v4) // Division operator overload
{
	x /= a_v4.x;
	y /= a_v4.y;
	z /= a_v4.z;
	w /= a_v4.w;
	return *this;
}

bool Vector4::operator ==(const Vector4& a_v4) const // Equal to operator
{
	return (x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.w);
}

bool Vector4::operator !=(const Vector4& a_v4) const // Not equal to operator
{
	return (x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);

}

float Vector4::magnitude() // Magnitude of the vector
{
	return sqrt(x*x + y*y + z*z + w*w);
}

float Vector4::magnitudeSquared() // Squared magnitude of the vector
{
	return x*x + y*y + z*z + w*w;
}

float Vector4::distanceBetweenVectors(Vector4&a_v4a, Vector4 &a_v4b) // Distance between the vectors
{
	return sqrt((a_v4a.x - a_v4a.x) * (a_v4a.x - a_v4b.x) + (a_v4a.y - a_v4a.y) * (a_v4a.y - a_v4b.y) + (a_v4a.z - a_v4b.z) * (a_v4a.z - a_v4b.z) + (a_v4a.w - a_v4b.w) * (a_v4a.w - a_v4b.w));
}

float Vector4::distanceBetweenVectorsSquared(Vector4 & a_v4a, Vector4 & a_v4b) // Squared Distance between the two vectors
{
	return (a_v4a.x - a_v4b.x) * (a_v4a.y - a_v4b.y) + (a_v4a.y - a_v4b.y) * (a_v4a.y - a_v4b.y) + (a_v4a.z - a_v4b.z) * (a_v4a.z - a_v4b.z) + (a_v4a.w - a_v4b.w) * (a_v4a.w - a_v4b.w);
}

void Vector4::normalise() // Normalises the vectors
{
	float length = magnitude();

	x = x / length;
	y = y / length;
	z = z / length;
	w = w / length;

}

float Vector4::dotProduct(Vector4 & a_v4a, Vector4 & a_v4b) // Dot product between the vectors
{
	return (a_v4a.x * a_v4b.x) + (a_v4a.y * a_v4b.y) + (a_v4a.z * a_v4b.z) + (a_v4a.w * a_v4b.w);
}

float Vector4::crossProduct(Vector4 & a_v4a, Vector4 & a_v4b) // Cross product between the vectors
{
	return (a_v4a.y * a_v4b.z - a_v4a.z * a_v4b.y, a_v4a.z * a_v4b.x - a_v4a.x * a_v4b.z, a_v4a.x * a_v4b.y - a_v4a.y * a_v4b.x, 0);
}