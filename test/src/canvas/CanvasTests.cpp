#include <canvas/Canvas.h>
#include <gtest/gtest.h>


TEST(CanvasTests, CanvasInit) {

	Canvas c(100, 200, Color(0.2, 2.0, 1.2));
	for (int i = 0; i < c.height; i++) {
		for (int j = 0; j < c.width; j++) {
			EXPECT_EQ(c.getColorAt(i, j), Color(0.2, 2.0, 1.2));
		}
	}

}

TEST(CanvasTests, SetGetColor) {
	Canvas c(100, 200);
	c.setColorAt(2, 10, Color(0.0f, 1.0f, 1.2f));
	EXPECT_EQ(c.getColorAt(2, 10), Color(0.0f, 1.0f, 1.2f));
}