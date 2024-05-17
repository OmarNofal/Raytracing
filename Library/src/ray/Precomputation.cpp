#include <ray/Precomputation.h>


Precomputation::Precomputation(
	const Intersection& i, 
	const Ray& r,
	const Intersections& xs
): s(i.s), t(i.t), n1(1.0f), n2(1.0f) {

	if (xs.empty()) {
		const_cast<Intersections&>(xs).push_back(i);
	}

	std::vector<const Shape*> containers{};

	for (auto& i2 : xs) {
		if (i2 == i) {
			if (containers.empty()) {
				n1 = 1.0f;
			}
			else {
				n1 = containers[containers.size() - 1]->material.refractiveIndex;
			}
		}

		auto pos = std::find(containers.begin(), containers.end(), i2.s);
		if (pos != containers.end()) {
			containers.erase(pos);
		}
		else {
			containers.push_back(i2.s);
		}

		if (i2 == i) {
			if (containers.empty()) {
				n2 = 1.0f;
			}
			else {
				n2 = containers[containers.size() - 1]->material.refractiveIndex;
			}
		}

	}

	point = r.positionAt(t);
	eyeV = -r.direction;
	normalV = s->normalAt(point);

	if (eyeV.dot(normalV) < 0) {
		inside = true;
		normalV = -normalV;
	}
	else {
		inside = false;
	}

	reflectv = r.direction.reflect(normalV);
	overPoint = point + EPSILON * normalV ;
	underPoint = point - EPSILON * normalV;
}

float Precomputation::schlick() const
{
	float cosineAngle = eyeV.dot(normalV);
	
	// check for total internal reflection
	if (n1 > n2) {
		float n = n1 / n2;
		float sin2_t = n * n * (1.0f - cosineAngle * cosineAngle);
		if (sin2_t > 1.0)
			return 1.0f;

		float cos_t = sqrtf(1.0f - sin2_t);
		cosineAngle = cos_t;
	}

	float r0 = powf(
		(n1 - n2) / (n1 + n2), 2.0f);

	return r0 + (1.0f - r0) * powf((1 - cosineAngle), 5.0f);
}
