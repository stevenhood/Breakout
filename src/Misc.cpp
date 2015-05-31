#include "Misc.h"

// Check if two DisplayableObjects overlap.
// Pointers are constant so the objects cannot be changed.
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


// Returns a random double between fMin and fMax - inclusive?
// http://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
double RandDouble(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


// Randomly returns either 1 or -1
int RandParity()
{
	return (rand() % 2 == 0) ? -1 : 1;
}
