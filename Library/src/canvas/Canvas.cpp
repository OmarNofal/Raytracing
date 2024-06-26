#include <canvas/Canvas.h>
#include <iostream>

Canvas::Canvas(size_t width, size_t height, Color initColor): width(width), height(height) {
	auto size = width * height;
	pixels = new Color[size];
	std::fill_n(pixels, size, initColor);
}

Canvas::Canvas(Canvas&& c) noexcept
{
	width = c.width;
	height = c.height;

	pixels = c.pixels;
	c.pixels = nullptr;
}

Canvas& Canvas::operator=(Canvas&& c) noexcept
{
	width = c.width;
	height = c.height;

	pixels = c.pixels;
	c.pixels = nullptr;
	return *this;
}

Color Canvas::getColorAt(size_t row, size_t column) const
{
	return pixels[width * row + column];
}

void Canvas::setColorAt(size_t row, size_t column, const Color& c) const
{
	if (row >= height || row < 0 || column >= width || column < 0) return;
	pixels[width * row + column] = c;
}


Canvas::~Canvas() {
	delete[] pixels;
}

