#pragma once
#include <math.h>



static bool compareFloats(float a, float b) {
	return fabs(a - b) <= 0.00001f;
}