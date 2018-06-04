#include "utils/render/Render.h"

void Test0()
{
  Camera main_camera = Camera();
  Render("src/objects/cube.obj", "sphere.bmp", main_camera);
}

int main()
{
  Test0();
  return 0;
}
