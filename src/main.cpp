#include "utils/Tracer.h"
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
  for (int i = 0; i < faces.size(); i++)
  {
    cout << faces[i].vertices[0]->pt.x << " ";
  }
  return 0;
}