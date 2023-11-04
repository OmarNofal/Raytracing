#pragma once
#include <math.h>



static bool compareFloats(float a, float b) {
	return fabsf(a - b) <= 0.005f;
}