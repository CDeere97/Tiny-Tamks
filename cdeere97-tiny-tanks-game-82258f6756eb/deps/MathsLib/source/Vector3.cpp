////////////////////////////////////////////////////////////
// File: Vector3.cpp
// Author: Chris Deere
// Date Created: 06/03/17
// Brief: Vector 3 file for CT4019 assignment 2 Tiny Tanks
////////////////////////////////////////////////////////////
#include "Vector3.h"
#include <cmath>

const Vector3 Vector3::ZERO = Vector3(0.f, 0.f, 0.f);
const Vector3 Vector3::AXIS_Y = Vector3(0.f, 1.f, 0.f);

Vector3::Vector3() // Initialises x, y and z to 0
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float a_x, float a_y, float a_z) // Initialises x, y and z to custom values
{
	x = a_x;
	y = a_y;
	z = a_z;
}

Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}

void Vector3::getPos(float& a_x, float& a_y, float a_z) const // Gets the x value
{
	a_x = x;
	a_y = y;
	a_z = z;
}



void Vector3::setPos(const float a_x, const float a_y, const float a_z) // Sets the x value
{
	x = a_x;
	y = a_y;
	z = a_z;
}

Vector3::~Vector3() // Destructor
{
}

Vector3 Vector3::operator +(const Vector3& a_v3) const // Addition operator
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}

Vector3& Vector3::operator +=(const Vector3& a_v3) // Addition operator overload
{
	x += a_v3.x;
	y += a_v3.y;
	z += a_v3.z;
	return *this;
}

Vector3 Vector3::operator -(const Vector3& a_v3) const // Subtraction operator
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}

Vector3& Vector3::operator -=(const Vector3& a_v3) // Subtraction operator overload
{
	x -= a_v3.x;
	y -= a_v3.y;
	z -= a_v3.z;
	return *this;
}


Vector3 Vector3::operator *(const Vector3& a_v3) const // Multiplication operator
{
	return Vector3(x * a_v3.x, y * a_v3.y, z * a_v3.z);
}

Vector3& Vector3::operator *=(const Vector3& a_v3) // Multiplication operator overload
{
	x *= a_v3.x;
	y *= a_v3.y;
	z *= a_v3.z;
	return *this;
}

Vector3 Vector3::operator *=(const float & a_f)
{
	this->x *= a_f;
	this->y *= a_f;
	this->z *= a_f;
	return*this ;
}

Vector3 Vector3::operator /(const Vector3& a_v3) const // Division operator
{
	return Vector3(x / a_v3.x, y / a_v3.y, z / a_v3.z);
}

Vector3& Vector3::operator /=(const Vector3& a_v3) // Division operator overload
{
	x /= a_v3.x;
	y /= a_v3.y;
	z /= a_v3.z;
	return *this;
}

bool Vector3::operator ==(const Vector3& a_v3) const // Equal to operator
{
	return (x == a_v3.x && y == a_v3.y && z == a_v3.z);
}

bool Vector3::operator !=(const Vector3& a_v3) const // Not equal to operator
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);

}

float Vector3::magnitude() // Magnitude of the vector
{
	return sqrt(x*x + y*y + z*z);
}

float Vector3::magnitudeSquared() // Squared magnitude of the vector
{
	return x*x + y*y + z*z;
}

float Vector3::distanceBetweenVectors(Vector3&a_v3a, Vector3 &a_v3b) // Distance between the vectors
{
	return sqrt((a_v3a.x - a_v3b.x) * (a_v3a.x - a_v3b.x) + (a_v3a.y - a_v3b.y) * (a_v3a.y - a_v3b.y) + (a_v3a.z - a_v3b.z) * (a_v3a.z - a_v3b.z));
}

float Vector3::distanceBetweenVectorsSquared(Vector3 & a_v3a, Vector3 & a_v3b) // Squared Distance between the two vectors
{
	return (a_v3a.x - a_v3b.x) * (a_v3a.x - a_v3b.x) + (a_v3a.y - a_v3b.y) * (a_v3a.y - a_v3b.y) + (a_v3a.z - a_v3b.z) * (a_v3a.z - a_v3b.z);
}

void Vector3::normalise() // Normalises the vectors
{
	float length = magnitude();

	x = x / length;
	y = y / length;
	z = z / length;

}

float Vector3::dotProduct(Vector3 & a_v3a, Vector3 & a_v3b) // Dot product between the vectors
{
	return (a_v3a.x * a_v3b.x) + (a_v3a.y * a_v3b.y) + (a_v3a.z * a_v3b.z);
}

float Vector3::crossProduct(Vector3 & a_v3a, Vector3 & a_v3b)
{
	return (a_v3a.y * a_v3b.z - a_v3a.z * a_v3b.y, a_v3a.z * a_v3b.x - a_v3a.x * a_v3b.z, a_v3a.x * a_v3b.y - a_v3a.y * a_v3b.x);
}


