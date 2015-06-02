#include <cmath>
#include "Utils.h"

bool IsCollideRect(DisplayableObject *const rect1, DisplayableObject *const rect2)
{
	if (rect1 == NULL || rect2 == NULL)
		return false;

	int x1, y1, w1, h1;
	x1 = rect1->GetX();
	y1 = rect1->GetY();
	w1 = rect1->GetWidth();
	h1 = rect1->GetHeight();

	int x2, y2, w2, h2;
	x2 = rect2->GetX();
	y2 = rect2->GetY();
	w2 = rect2->GetWidth();
	h2 = rect2->GetHeight();

	// If true, it is impossible that the two rectangles are overlapping
	return !(x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
}

double RandDouble(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int RandParity()
{
	return (rand() % 2 == 0) ? -1 : 1;
}
