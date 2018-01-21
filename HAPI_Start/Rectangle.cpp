#include "Rectangle.h"




void Rectangle::ClipTo(const Rectangle &other)
{
	if (left < other.left)
	{
		left = other.left;
	}
	if (right > other.right)
	{
		right = other.right;
	}
	if (top < other.top)
	{
		top = other.top;
	}
	if (bottom > other.bottom)
	{
		bottom = other.bottom;
	}
}

bool Rectangle::CompletelyContains(const Rectangle &other) const
{

	if (left < other.left)
		return false;
	if (right > other.right)
		return false;
	if (top < other.top)
		return false;
	if (bottom > other.bottom)
		return false;

	return true;
}

bool Rectangle::CompletelyOutside(const Rectangle &other) const
{
	if (left > other.right)
	{
		return true;
	}
	if (right < other.left)
	{
		return true;
	}
	if (top > other.bottom)
	{
		return true;
	}
	if (bottom < other.top)
	{
		return true;
	}

	return false;

}

void Rectangle::Translate(int dx, int dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}


//We use this function to reduce size by a % amount to suit collisions
void Rectangle::ReduceRectangleSize(int amount)
{
	int wReduced = amount * Width() / 100;
	int hReduced = amount * Height() / 100;

	left += wReduced/2;
	right -= wReduced/2;
	top += hReduced/2;
	bottom -= hReduced/2;
}