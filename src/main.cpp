#include "utils/render/Render.h"

void Test0()
{
  Camera main_camera = Camera();
  Render("src/objects/cube.obj", "render.bmp", main_camera);
}

void Test1()
{
  cout << sizeof(Vector) << endl;
  cout << sizeof(Vertex) << endl;
  cout << sizeof(Facet) << endl;
}

int main()
{
  Test0();
  return 0;
}
