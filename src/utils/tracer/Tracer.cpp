#include "Tracer.h"

using namespace std;

Vector::Vector()
{
  x = 0;
  y = 0;
  z = 0;
}

Vector::Vector(const float coordinates[3])
{
  x = coordinates[0];
  y = coordinates[1];
  z = coordinates[2];
}

Vector::Vector(vector<float> vector)
{
  x = vector[0];
  y = vector[1];
  z = vector[2];
}

Vector::Vector(float X, float Y, float Z): x(X), y(Y), z(Z) {}

Vertex::Vertex(Vector vec)
{
  pt = vec;
}

Facet::Facet(Vector v1, Vector v2, Vector v3)
{
  v[0] = v1;
  v[1] = v2;
  v[2] = v3;
}

void Tracer::parseOBJ(const char *fname, vector<Vertex> &vertices, vector<Facet> &faces)
{
  ifstream file(fname);

  vertices.clear();
  faces.clear();

  string str;

  if (file.is_open())
  {
    while (file.good())
    {
      getline(file, str);
      switch (str[0])
      {
      case 'v':
      {
        vector<string> coords = strsplit<string>(str, ' ');
        vertices.push_back(Vertex(Vector(stof(coords[1]), stof(coords[2]), stof(coords[3]))));
        break;
      }
      case 'f':
      {
        vector<string> pts = strsplit<string>(str, ' ');
        int v1 = stoi(strsplit<string>(pts[1], '/')[0]),
                v2 = stoi(strsplit<string>(pts[2], '/')[0]),
                v3 = stoi(strsplit<string>(pts[3], '/')[0]);
        Facet f(vertices[v1].pt, vertices[v2].pt, vertices[v3].pt);
        faces.push_back(f);
        vertices[v1].facets.push_back(f);
        vertices[v2].facets.push_back(f);
        vertices[v3].facets.push_back(f);
        break;
      }
      default:
        break;
      }
    }
  }
  else
  {
    log("Error opening " + (string)fname);
  }
}

// Vector Tracer::local_to_world(Vector *child, Vector *parent)
// {
//   const float c[3] = {child->x + parent->x, child->y + parent->y, child->z + parent->z};
//   return Vector(c);
// }
// Vector Tracer::world_to_local(Vector *child, Vector *parent)
// {
//   const float c[3] = {child->x - parent->x, child->y - parent->y, child->z - parent->z};
//   return Vector(c);
// }

template <typename T>
void log(T content)
{
  cout << content << endl;
}

pair<bool, pair<Vector, Ray> > Tracer::intersectsRectangle(Vector up, Vector down, Ray ray) {
  pair<bool, pair<Vector, Ray> > ans;
  return ans;
}

pair<bool, pair<Vector, Ray> > Tracer::intersectsTriangle(Facet facet, Ray ray) {
  pair<bool, pair<Vector, Ray> > ans;
  return ans;
}

template <class T>
vector<T> strsplit(string input, char delimiter)
{
  vector<T> res;
  string sub;
  size_t pos = input.find_first_of(delimiter);
  while (pos < input.length() && pos > 0)
  {
    sub = input.substr(0, pos);
    input = input.substr(pos + 1);
    pos = input.find_first_of(' ');
    res.push_back(static_cast<T>(sub));
  }
  res.push_back(static_cast<T>(input.substr(0, pos)));
  return res;
}
