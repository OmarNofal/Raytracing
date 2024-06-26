#ifndef TUPLE_H
#define TUPLE_H

class Tuple {

public:
	float x, y, z, w;

	Tuple(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) noexcept;
	
	bool isVector() const;
	bool isPoint() const;


	bool operator==(const Tuple& t) const;
	Tuple operator+(const Tuple& t) const;
	Tuple operator-(const Tuple& t) const;
	Tuple operator-() const;
	Tuple operator*(float scalar) const;

	float magnitude() const;
	Tuple normalized() const;
	Tuple reflect(const Tuple&) const;

	float dot(const Tuple&) const;
	Tuple cross(const Tuple&) const;

	static Tuple createVector(float, float, float);
	static Tuple createPoint(float, float, float);

	

};

static Tuple point(float x, float y, float z) {
	return Tuple::createPoint(x, y, z);
}

static Tuple vector(float x, float y, float z) {
	return Tuple::createVector(x, y, z);
}

static Tuple operator*(float scalar, const Tuple& t) {
	return t * scalar;
}

#endif