#include <material/Pattern.h>
#include <cmath>
#include <geometry/Shape.h>




StripePattern::StripePattern(const Color& a, const Color& b) noexcept : a(a), b(b) {}

Color StripePattern::getColorAt(const Tuple& t) const { 
	auto floored = (int) std::floorf(t.x);
	if (floored % 2 == 0) return a; else return b;
};

Color Pattern::getColorAtObject(const Shape& s, const Tuple& t) const {
	Tuple localPoint = this->transform.inverse() * (s.transform.inverse() * t);
	return getColorAt(localPoint);
};

GradientPattern::GradientPattern(const Color& a, const Color& b) noexcept: a(a), b(b)
{
}

Color GradientPattern::getColorAt(const Tuple& p) const
{
	Color distance = b - a;
	Color color = a + distance * (p.x - std::floorf(p.x));
	return color;
}

RingPattern::RingPattern(const Color& a, const Color& b) noexcept: a(a), b(b) 
{
}

Color RingPattern::getColorAt(const Tuple& p) const
{
	int floored = (int) sqrtf( floorf(p.x*p.x + p.z * p.z) );
	if (floored % 2 == 0) return a; else return b;
}

CheckerPattern::CheckerPattern(const Color& a, const Color& b) noexcept: a(a), b(b) {

}

Color CheckerPattern::getColorAt(const Tuple& p) const 
{
	int floored = floorf(p.x) + floorf(p.y) + floorf(p.z);
	if (floored % 2 == 0) return a;
	else return b;
}