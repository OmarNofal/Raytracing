#include <vec/Tuple.h>
#include <utils/FloatUtils.h>


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

bool Tuple::operator==(const Tuple& t) const
{
	return compareFloats(t.x, this->x)
		&& compareFloats(t.y, this->y)
		&& compareFloats(t.z, this->z)
		&& compareFloats(t.w, this->w);
}

Tuple Tuple::operator+(const Tuple& t) const
{
	return Tuple(t.x + this->x, t.y + this->y, t.z + this->z, t.w + this->w);
}

Tuple Tuple::operator-(const Tuple& t) const
{
	return Tuple(this->x - t.x, this->y - t.y, this->z - t.z, this->w - t.w);
}

Tuple Tuple::operator-() const
{
	return Tuple(-this->x, -this->y, -this->z, -this->w);
}

Tuple Tuple::operator*(float scalar) const
{
	return Tuple(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}

float Tuple::magnitude() const
{
	auto squared = this->x * this->x
		+ this->y * this->y
		+ this->z * this->z
		+ this->w * this->w;
	return sqrtf(squared);
}

Tuple Tuple::normalized() const
{
	float magnitude = this->magnitude();
	return Tuple(this->x/magnitude, this->y/magnitude, this->z/magnitude, this->w/magnitude);
}

Tuple Tuple::reflect(const Tuple& t) const
{
	return *this - 2 * this->dot(t) * t;
}

float Tuple::dot(const Tuple& t) const {
	return this->x * t.x + this->y * t.y + this->z * t.z + this->w * t.w;
}

Tuple Tuple::cross(const Tuple& t) const {
	return Tuple::createVector(
		this->y * t.z - t.y * this->z,
		this->z * t.x - t.z * this->x,
		this->x * t.y - t.x * this->y
	);
}

Tuple Tuple::createVector(float x, float y, float z) {
	return Tuple(x, y, z, 0.0f);
}