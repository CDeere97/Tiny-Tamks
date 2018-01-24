#include "Position.h"

void Position::Get(float& a_x, float& a_y)
{
	a_x = x;
	a_y = y;
}

void Position::Set(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

Position::Position()
{
	x = 0.f;
	y = 0.f;
}

