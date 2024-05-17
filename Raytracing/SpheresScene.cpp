//CheckerPattern* s = new CheckerPattern(Color(), Color(1, 1, 1));
//s->transform = Mat4(1.0f).scale(0.1f, 3, 0.1f);
//
//Sphere middle;
//middle.transform = Mat4(1.0f)
//.translate(-.5f, 1.0, -3.0);
//middle.material.color = Color(1.0f, 1.0f, 1.0f);
//middle.material.ambient = 0.1f;
//middle.material.diffuse = 0.4f;
//middle.material.specular = 0.2f;
//middle.material.shininess = 300;
//middle.material.reflective = 0.9f;
//middle.material.transperancy = 0.0f;
//middle.material.refractiveIndex = 1.5f;
////middle.material.pattern.reset(s);
//
//GradientPattern* g = new GradientPattern(Color(0, 0, 1), Color(1, 0, 0));
//g->transform = Mat4(1.0f).scale(3.0f, 1, 1);
//
//Sphere smallSphere;
//smallSphere.transform = Mat4(1.0f)
//.scale(0.5, 0.5, 0.5)
//.translate(1.5f, 0.5f, -0.5f);
//smallSphere.material.color = Color(0.5, 1, 0.1);
//smallSphere.material.diffuse = 0.7f;
//smallSphere.material.specular = 0.3f;
//smallSphere.material.pattern.reset(g);
//
//
//Light l(Tuple::createPoint(-10, 10, -10));
//
//Camera c(1000, 1000, M_PI / 3.0f);
//c.transform = viewMatrix(
//	point(0, 1.5, -5),
//	point(0, 1, 0),
//	vector(0, 1, 0)
//);
//
//
//Plane floor;
//floor.material.color = Color(0.2f, 0.6f, 0.2f);
//floor.material.reflective = 0.3f;
//floor.material.setPattern(new CheckerPattern(Color(), Color(1, 1, 1)));
//
//
//GradientPattern* g2 = new GradientPattern(Color(0.3f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.3f));
//g2->transform = Mat4(1.0f).scale(10.0f, 1, 1);
//
//Plane backWall;
//backWall.material.color = Color(0.4f, 0.2f, 0.4f);
//backWall.transform = Mat4(1.0f).rotate(M_PI / 2.0f, 0, 0).translate(0, 0, 10.0f);
//backWall.material.specular = 0.0f;
////backWall.material.pattern.reset(g2);
//
//World w;
//w.shapes.push_back(&backWall);
//w.shapes.push_back(&smallSphere);
//w.shapes.push_back(&middle);
//w.shapes.push_back(&floor);
//
//w.lights.push_back(l);