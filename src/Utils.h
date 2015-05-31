#pragma once
#include "DisplayableObject.h"

// Check if two DisplayableObjects overlap.
// Pointers are constant so the objects cannot be changed.
bool IsCollideRect(DisplayableObject *const rect1, DisplayableObject *const rect2);

// Returns a random double between fMin and fMax - inclusive?
// http://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
double RandDouble(double fMin, double fMax);

// Randomly returns either 1 or -1
int RandParity();
