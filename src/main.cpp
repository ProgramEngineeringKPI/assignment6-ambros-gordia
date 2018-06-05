#include "utils/render/Render.hpp"

void Test0()
{
    Camera main_camera = Camera();
    Render("/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/objects/sphere.obj", "/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/sphere.bmp", main_camera);
}

void Test1() {
    Tracer tr;
    Ray r(Vector(5, 4, 1.5), Vector(-0.762942, -1.14439, 0.170066));
    cout<<tr.intersectsBox(Vector(1, -1, 1), Vector(-1, -1, -1), r)<<endl;
}

int main()
{
    Test0();
    //Test1();
}

