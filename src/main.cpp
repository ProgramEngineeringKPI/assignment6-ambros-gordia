#include "utils/render/Render.hpp"

void Test0()
{
<<<<<<< HEAD
    Camera main_camera = Camera();
    Render("/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/objects/sphere.obj", "/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/sphere.bmp", main_camera);
}

void Test1() {
    Tracer tr;
    Ray r(Vector(5, 4, 1.5), Vector(-0.762942, -1.14439, 0.170066));
    cout<<tr.intersectsBox(Vector(1, -1, 1), Vector(-1, -1, -1), r)<<endl;
=======
  Camera main_camera = Camera();
  Render("src/objects/sphere.obj", "render.bmp", main_camera);
}

void Test1()
{
  cout << sizeof(Vector) << endl;
  cout << sizeof(Vertex) << endl;
  cout << sizeof(Facet) << endl;
>>>>>>> geometry
}

int main()
{
<<<<<<< HEAD
    Test0();
    //Test1();
=======
  Tracer tr;
  // Test0();
  for (int i = 0; i < 1000000000; i++)
  {
    Vector *vv = new Vector(1, 0, 2);
    Facet *f = new Facet(*vv, *vv, *vv);
    Ray* r = new Ray(*vv, *vv);
    pair<Vector, Vector> v = tr.intersectsTriangle(*f, *r);
    delete vv;
    delete f;
    delete r;
  }
  return 0;
>>>>>>> geometry
}

