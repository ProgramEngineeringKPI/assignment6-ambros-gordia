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

Vertex::Vertex(Vector vec, Facet *facet, int facet_count)
{
  pt = vec;
  f = facet;
  facet_count = facet_count;
}

void Tracer::parseOBJ(const char *fname, vector<Vertex> &vertices, vector<Facet> &faces)
{
  ifstream file(fname);

  vector<Vector> points;
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
        float p[3];
        vector<string> coords = strsplit<string>(str, ' ');
        Vector v;
        v.x = stof(coords[1]);
        v.y = stof(coords[2]);
        v.z = stof(coords[3]);
        points.push_back(v);
        break;
      }
      case 'f':
      {
        vector<string> pts = strsplit<string>(str, ' ');
        log("arr init");
        Facet facet;
        int vnums[3];
        for (int i = 1; i < pts.size(); i++) // f 1// 2// 3//
        {
          vnums[i - 1] = stoi(strsplit<string>(pts[i], '/')[0]);
        }
        for (int i = 0; i < 3; i++)
        {
          log("point created");
          Vertex v = Vertex(points[vnums[i]], &facet, pts.size() - 1);
          vertices.push_back(v);
          log("vertex pushed");
          facet.vertices[i] = &v;
        }
        faces.push_back(facet);
        break;
      }
      default:
        break;
      }
    }

    for (vector<Vector>::iterator it = points.begin(); it != points.end(); it++)
    {
      log(to_string(it->x) + " " + to_string(it->y) + " " + to_string(it->z));
    }
  }
  else
  {
    log("Error opening " + (string)fname);
  }
}

bool Tracer::intersectsTriangle(Facet facet, Ray ray)
{
}
bool Tracer::intersectsRectangle(Vector up, Vector down, Ray ray)
{
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

template <class T>
vector<T> strsplit(string input, char delimiter)
{
  vector<T> res;
  string sub;
  size_t pos = input.find_first_of(' ');
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
