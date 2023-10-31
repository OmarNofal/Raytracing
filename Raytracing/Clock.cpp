#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

void drawClock() {
	/*srand(time(NULL));

	Canvas c{ 100, 100 };

	for (int i = 0; i < 12; i++) {

		auto p = Tuple::createPoint(0, -1, 0);

		float angle = i * (2 * M_PI / 12.0f);

		auto m = Mat4::identity()
			.rotate(0, 0, angle)
			.scale(c.width / 4.0f, c.height / 4.0f, 0)
			.translate(c.width / 2.0f, c.height / 2.0f, 0);

		auto newPoint = m * p;

		printf("Point %d: %2.f, %2.f, %2.f\n", i, newPoint.x, newPoint.y, newPoint.z);

		c.setColorAt(newPoint.x, newPoint.y, Color((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
	}

	SaveCanvas("out.jpg", c);*/
}

