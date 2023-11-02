#include <camera/Camera.h>



Camera::Camera(
	size_t hSize, 
	size_t vSize, 
	float fov,
	Mat4 transform
): hSize(hSize), vSize(vSize), fov(fov), transform(transform) {

	float halfView = tanf(fov / 2.0f);

	float aspect = ( (float) hSize ) / vSize;

	if (aspect >= 1.0f)
	{
		halfWidth = halfView;
		halfHeight = halfView / aspect;
	}
	else {
		halfHeight = halfView;
		halfWidth = halfView * aspect;
	}

	pixelSize = (halfWidth * 2) / ((float) hSize);
}

Ray Camera::rayForPixel(size_t x, size_t y) const
{

	float xOffset = (x + 0.5f) * pixelSize;
	float yOffset = (y + 0.5f) * pixelSize;

	float worldX = (halfWidth - xOffset);
	float worldY = (halfHeight - yOffset);

	auto pixel = transform.inverse() *
		Tuple::createPoint(worldX, worldY, -1.0f);

	auto origin = transform.inverse() * Tuple::createPoint(0, 0, 0);

	auto direction = (pixel - origin).normalized();


	return Ray(origin, direction);
}

Canvas Camera::render(const World& w, bool verbose) const
{
	Canvas c(hSize, vSize);

	if (verbose)
		printf("Rendering image\n");

	for (int y = 0; y < vSize; y++) {

		if (verbose) {
			printf("\33[2K\rProgress: %2.f%%", (y * vSize) / ((float)hSize * vSize) * 100);
		}

		for (int x = 0; x < hSize; x++) {

			

			auto ray = rayForPixel(x, y);
			auto color = w.colorAt(ray);
			c.setColorAt(y, x, color);

		}

	}

	return c;
}
