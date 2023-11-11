#include <material/Pattern.h>
#include <material/Material.h>
#include <gtest/gtest.h>
#include <geometry/Sphere.h>


TEST(PatternTests, StripePatternInit) {

	Color c1;
	Color c2(1, 1, 1);

	StripePattern s(c1, c2);

	EXPECT_EQ(s.a, c1);
	EXPECT_EQ(s.b, c2);
}

TEST(PatternTests, StripePatterFunction) {

	Color c1;
	Color c2(1, 1, 1);

	StripePattern s(c1, c2);

	auto e1 = s.getColorAt(point(0, 0, 1));
	auto e2 = s.getColorAt(point(0, 0, 2));
	auto e3 = s.getColorAt(point(0, 1, 0));
	auto e4 = s.getColorAt(point(0, 2, 1));
	auto e5 = s.getColorAt(point(1, 0, 1));
	auto e6 = s.getColorAt(point(0, 0, 1));
	auto e7 = s.getColorAt(point(0.9, 0, 1));
	auto e8 = s.getColorAt(point(-0.1, 0, 1));

	EXPECT_EQ(e1, c1);
	EXPECT_EQ(e2, c1);
	EXPECT_EQ(e3, c1);
	EXPECT_EQ(e4, c1);
	EXPECT_EQ(e5, c2);
	EXPECT_EQ(e6, c1);
	EXPECT_EQ(e7, c1);
	EXPECT_EQ(e8, c2);
}

TEST(PatternTests, CheckerPatternFunction) {

	Sphere s;
	CheckerPattern* p = new CheckerPattern(Color::white(), Color::black());
	s.material.pattern.reset(p);

	// repeats in x
	EXPECT_EQ(p->getColorAtObject(s, point(0, 0, 0)), Color::white());
	EXPECT_EQ(p->getColorAtObject(s, point(0.99f, 0, 0)), Color::white());
	EXPECT_EQ(p->getColorAtObject(s, point(1.01f, 0, 0)), Color::black());

	// repeats in y
	EXPECT_EQ(p->getColorAtObject(s, point(0, 1.01f, 0)), Color::black());
	EXPECT_EQ(p->getColorAtObject(s, point(0, 0.9f, 0)), Color::white());

	// repeats in z
	EXPECT_EQ(p->getColorAtObject(s, point(0, 0, 1.01)), Color::black());
	EXPECT_EQ(p->getColorAtObject(s, point(0, 0, 0.99)), Color::white());
}

TEST(PatternTests, RingPatternFunction) {

	Color white(1, 1, 1);
	Color black(0, 0, 0);

	RingPattern r(white, black);
	EXPECT_EQ(r.getColorAt(point(0, 0, 0)), white);
	EXPECT_EQ(r.getColorAt(point(1, 0, 0)), black);
	EXPECT_EQ(r.getColorAt(point(0, 0, 1)), black);
	EXPECT_EQ(r.getColorAt(point(0.708f, 0, 0.708f)), black);
}
TEST(PatternTests, GradientPatternFunction) {

	Color c1(1,1,1);
	Color c2;

	GradientPattern s(c1, c2);

	auto e1 = s.getColorAt(point(0.25f, 0, 1));
	auto e2 = s.getColorAt(point(0.5f, 0, 2));
	auto e3 = s.getColorAt(point(0.75f, 1, 0));


	EXPECT_EQ(e1, Color(0.75, 0.75, 0.75));
	EXPECT_EQ(e2, Color(0.5,0.5,0.5));
	EXPECT_EQ(e3, Color(0.25, 0.25, 0.25));
}

TEST(PatternTests, StripesTransformation) {

	Sphere s;
	StripePattern* p = new StripePattern(Color(1,1,1), Color());
	s.transform = Mat4(1.0f).scale(2, 2, 2);
	s.material.pattern.reset(p);

	EXPECT_EQ(p->getColorAtObject(s, point(1.5, 0, 0)), Color(1, 1, 1));

	s.transform = Mat4(1.0f);
	p->transform = Mat4(1.0f).scale(2, 2, 2);
	EXPECT_EQ(p->getColorAtObject(s, point(1.5, 0, 0)), Color(1, 1, 1));

	s.transform = Mat4(1.0f).scale(2, 2, 2);
	p->transform = Mat4(1.0f).translate(0.5, 0, 0);
	EXPECT_EQ(p->getColorAtObject(s, point(2.5, 0, 0)), Color(1, 1, 1));

}
