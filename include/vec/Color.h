
#ifndef COLOR_H
#define COLOR_H

#include "Tuple.h"


class Color : public Tuple {

public:
	float& r = x, & g = y, & b = z;


	Color(float r = 0.0f, float g = 0.0f, float b = 0.0f) noexcept;

	Color& operator=(const Color&);
	Color(const Color&);

	Color operator+(const Color&) const;
	Color operator*(const Color&) const; // hadamard product
	Color operator-(const Color&) const;
	Color operator*(float scalar) const;
	bool operator==(const Color&) const;

	static Color fromTuple(const Tuple&);
	static Color black() { return Color(0, 0, 0); };
	static Color white() { return Color(1, 1, 1); };

private:
	using Tuple::x;
	using Tuple::y;
	using Tuple::z;
	using Tuple::cross;
	using Tuple::dot;
};


static Color operator*(float scalar, const Color& t) {
	return t * scalar;
}


#endif