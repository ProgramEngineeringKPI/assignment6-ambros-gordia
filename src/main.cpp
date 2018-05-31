#include "utils/tracer/Tracer.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  vector<Vertex> verts;
  vector<Facet> faces;
  Tracer t;
  t.parseOBJ("./test/test.obj", verts, faces);

}