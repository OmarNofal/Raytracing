#include <vec/Tuple.h>



Tuple::Tuple(float x, float y, float z, float w) noexcept :
	x(x), y(y), z(z), w(w) {};


bool Tuple::isVector() const {
	return this->w == 0.0f;
}

bool Tuple::isPoint() const {
	return this->w == 1.0f;
}

Tuple Tuple::createPoint(float x, float y, float z) {
	return Tuple(x, y, z, 1.0f);
}

Tuple Tuple::createVector(float x, float y, float z) {
	return Tuple(x, y, z, 0.0f);
}