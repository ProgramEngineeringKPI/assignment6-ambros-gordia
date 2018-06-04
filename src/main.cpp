#include "utils/render/Render.h"

void Test0()
{
  Camera main_camera = Camera();
  Render("/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/objects/cube.obj", "/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/sphere.bmp", main_camera);
}

int main()
{
  Test0();
}
