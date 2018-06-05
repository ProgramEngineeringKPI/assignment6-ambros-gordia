#include "utils/render/Render.h"

void Test0()
{
  Camera main_camera = Camera();
  Render("src/objects/sphere.obj", "render.bmp", main_camera);
}

void Test1()
{
  cout << sizeof(Vector) << endl;
  cout << sizeof(Vertex) << endl;
  cout << sizeof(Facet) << endl;
}

int main()
{
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
}
