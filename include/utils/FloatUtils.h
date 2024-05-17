#pragma once
#include <math.h>


constexpr float EPSILON = 0.005f;

static bool compareFloats(float a, float b) {
	return fabsf(a - b) <= EPSILON;
}