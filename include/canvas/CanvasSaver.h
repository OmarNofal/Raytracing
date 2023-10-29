#pragma once

#include "Canvas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


static float clamp(float lo, float high, float num) {
	return std::max(lo, std::min(high, num));
}

static float clampPixelColor(float num) {
	return clamp(0, 1, num);
}

static void SaveCanvas(const Canvas& canvas) {

	auto numPixels = canvas.width * canvas.height;

	auto image = new unsigned char[numPixels * 3];

	for (int i = 0; i < canvas.height; i++) {

		for (int j = 0; j < canvas.width; j++) {

			Color c = canvas.getColorAt(i, j);
			const auto colorStart = (i * canvas.width + j) * 3;

			image[colorStart + 0] = clampPixelColor(c.r) * 255;
			image[colorStart + 1] = clampPixelColor(c.g) * 255;
			image[colorStart + 2] = clampPixelColor(c.b) * 255;
		}

	}

	stbi_write_jpg("out.jpg", canvas.width, canvas.height, 3, image, 100);

	delete[] image;
}