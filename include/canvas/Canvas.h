#pragma once
#include <array>
#include <vec/Color.h>

class Canvas {

private:
	Color* pixels = nullptr; // row-major order

public:
	size_t width;
	size_t height;

	Canvas(size_t width, size_t height, Color initColor = Color(0, 0, 0));
	~Canvas();

	Canvas(const Canvas& c) = delete;
	Canvas& operator=(const Canvas& c) = delete;


	Canvas(Canvas&& c) noexcept;
	Canvas& operator=(Canvas&& c) noexcept;

	Color getColorAt(size_t row, size_t column) const;
	void setColorAt(size_t row, size_t column, const Color&) const;

};