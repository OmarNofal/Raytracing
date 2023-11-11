#pragma once

#include <vec/Color.h>
#include <linalg/Matrix.h>

class Shape;

class Pattern {


public:

	Mat4 transform = Mat4(1.0f);

	virtual Color getColorAt(const Tuple& p) const = 0;

	Color getColorAtObject(const Shape&, const Tuple&) const;

};


class StripePattern : public Pattern {

public:
	Color a, b;
	StripePattern(const Color& a, const Color& b) noexcept;

	Color getColorAt(const Tuple& p) const override;
};


class GradientPattern : public Pattern {

public:
	Color a, b;
	GradientPattern(const Color& a, const Color& b) noexcept;

	Color getColorAt(const Tuple& p) const override;
};


class RingPattern : public Pattern {

public:
	Color a, b;
	RingPattern(const Color& a, const Color& b) noexcept;

	Color getColorAt(const Tuple& p) const override;
};


class CheckerPattern : public Pattern {

public:
	Color a, b;
	CheckerPattern(const Color& a, const Color& b) noexcept;

	Color getColorAt(const Tuple& p) const override;
};