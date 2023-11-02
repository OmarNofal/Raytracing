#pragma once
#include <vec/Color.h>
#include <utils/FloatUtils.h>


Color::Color(float r, float g, float b) noexcept: Tuple(r, g, b, 0.0f) {}

Color& Color::operator=(const Color& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	return *this;
}

Color::Color(const Color& c)
{
	r = c.r;
	g = c.g;
	b = c.b;
}

Color Color::operator+(const Color& c) const
{
	return Color{ this->r + c.r, this->g + c.g, this->b + c.b };
}

Color Color::operator*(const Color& c) const
{
	return Color(this->x * c.x, this->y * c.y, this->z * c.z);
}

Color Color::operator-(const Color& c) const
{
	return Color{ this->r - c.r, this->g - c.g, this->b - c.b };
}

Color Color::operator*(float scalar) const
{
	return Color(this->x * scalar, this->y * scalar, this->z * scalar);
}

bool Color::operator==(const Color& c) const {
	return compareFloats(c.x, this->x)
		&& compareFloats(c.y, this->y)
		&& compareFloats(c.z, this->z);
}

Color Color::fromTuple(const Tuple& t) {
	return Color(t.x, t.y, t.z);
}

