#include <geometry/Shape.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

class Cone : public Shape {

public:
	Cone() noexcept = default;
	
	float minimum = -std::numeric_limits<float>::infinity();
	float maximum = std::numeric_limits<float>::infinity();

	float closed = false;

private:
	Tuple localNormalAt(const Tuple& t) const override;
	Intersections localIntersect(const Ray& r) const override;
	bool checkCapIntersection(const Ray& r, float t, float radius) const;
	void intersectCaps(const Ray& r, Intersections& xs) const;
};