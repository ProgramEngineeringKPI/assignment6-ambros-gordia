#include "src/utils/rtree/RTree.h"

void Test1() // testing vector struct
{
	Vector v1 = Vector(6, 7, 10);
	Vector v2 = Vector(8, 5, 9);
	Vector v3 = v1.cross(v2);
	cout << v3.x << v3.y << v3.z;
	if (v1.cross(v2) == v2)
		cout << "\033[30;42m:Passed:\033[0m" << endl;
	else
		cout << "\033[30;41m:Errored:\033[0m" << endl;
}

void Test2()
{
	string path;
	cout << "Write file path:\n> ";
	// cin >> path;
	path = "src/objects/cube.obj";
	Tracer t;
	t.Render(path.c_str(), "render.bmp");
}

void Test3() // testing intersection
{
	Tracer t;
	Vector
		v1 = Vector(0, 4, 0),
		v2 = Vector(4, 0, 3),
		v3 = Vector(4, 0, -3),
		orig = Vector(0, 0, 0),
		dir = Vector(1, .5, 0);

	Facet f = Facet(v1, v2, v3);
	Ray r = Ray(orig, dir);
	Vector intersect = t.intersectsTriangle(f, r);
	if (intersect)
	{
		cout << "Intersects: ";
		intersect.print();
	}
	else
	{
		cout << v1.x;
	}
}

int main()
{
	Test2();
	return 0;
}