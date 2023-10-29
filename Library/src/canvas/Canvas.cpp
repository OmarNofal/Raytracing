#include <canvas/Canvas.h>


Canvas::Canvas(size_t width, size_t height, Color initColor): width(width), height(height) {
	auto size = width * height;
	pixels = new Color[size];
	std::fill_n(pixels, size, initColor);
}

Color Canvas::getColorAt(size_t row, size_t column) const
{
	return pixels[width * row + column];
}

void Canvas::setColorAt(size_t row, size_t column, const Color& c) const
{
	pixels[width * row + column] = c;
}


Canvas::~Canvas() {
	delete[] pixels;
}

