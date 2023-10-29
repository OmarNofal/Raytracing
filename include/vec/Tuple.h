#pragma once


class Tuple {

public:
	float x, y, z, w;

	Tuple(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) noexcept;
	
	bool isVector() const;
	bool isPoint() const;

	Tuple() = delete;


	bool operator==(const Tuple& t) const;
	Tuple operator+(const Tuple& t) const;
	Tuple operator-(const Tuple& t) const;
	Tuple operator-() const;
	Tuple operator*(float scalar) const;

	float magnitude() const;
	Tuple normalized() const;

	float dot(const Tuple&) const;
	Tuple cross(const Tuple&) const;

	static Tuple createVector(float, float, float);
	static Tuple createPoint(float, float, float);

};