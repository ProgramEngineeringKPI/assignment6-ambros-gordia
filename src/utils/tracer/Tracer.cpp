#include "Tracer.h"

using namespace std;

Camera main_camera;

Vector::Vector() : x(0), y(0), z(0) {}

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

Vector::Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

Vector::operator bool()
{
  return intersects;
}

Vector Vector::operator+(Vector &v)
{
  return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator-(Vector &v)
{
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float num)
{
  return Vector(x * num, y * num, z * num);
}

bool Vector::operator==(Vector &v)
{
  return (x == v.x) && (y == v.y) && (z == v.z);
}

float Vector::dot(Vector &v)
{
  return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(Vector &v)
{
  return Vector(
      y * v.z - z * v.y,
      z * v.x - x * v.z,
      x * v.y - y * v.x);
}

Vector Vector::normalize()
{
  float l = sqrtf(x * x + y * y + z * z);
  return *new Vector(x / l, y / l, z / l);
}

float Vector::length()
{
  return sqrtf(x * x + y * y + z * z);
}

void Vector::print()
{
  cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vertex::Vertex(Vector vec)
{
  pt = vec;
}

Facet::Facet(Vector &v1, Vector &v2, Vector &v3)
{
  v[0] = v1;
  v[1] = v2;
  v[2] = v3;
}

Ray::Ray(Vector _origin, Vector _direction)
{
  origin = _origin;
  direction = _direction;
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
        if (str[1] == ' ')
        {
          vector<string> coords = strsplit<string>(str, ' ');
          vertices.push_back(Vertex(Vector(stof(coords[1]), stof(coords[2]), stof(coords[3]))));
        }
        break;
      }
      case 'f':
      {
        vector<string> pts = strsplit<string>(str, ' ');
        int v1 = stoi(strsplit<string>(pts[1], '/')[0]) - 1,
            v2 = stoi(strsplit<string>(pts[2], '/')[0]) - 1,
            v3 = stoi(strsplit<string>(pts[3], '/')[0]) - 1;
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
  cout << "Vertex count: " << vertices.size() << "\n Faces count: " << faces.size() << "\n";
}

pair<Vector, Vector> Tracer::intersectsTriangle(Facet &facet, Ray &ray)
{
  const float E = 1e-51;
  float
      x0 = facet.v[0].x,
      y0 = facet.v[0].y,
      z0 = facet.v[0].z,
      x1 = facet.v[1].x,
      y1 = facet.v[1].y,
      z1 = facet.v[1].z,
      x2 = facet.v[2].x,
      y2 = facet.v[2].y,
      z2 = facet.v[2].z,

      A = (y1 - y0) * (z2 - z0) - (y2 - y0) * (z1 - z0),
      B = (x2 - x0) * (z1 - z0) - (x1 - x0) * (z2 - z0),
      C = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0),
      D =
          x0 * ((y2 - y0) * (z1 - z0) - (y1 - y0) * (z2 - z0)) +
          y0 * ((x1 - x0) * (z2 - z0) - (x2 - x0) * (z1 - z0)) +
          z0 * ((y1 - y0) * (x2 - x0) - (x1 - x0) * (y2 - y0)),

      t =
          -(A * ray.origin.x + B * ray.origin.y + C * ray.origin.z + D) /
          (A * ray.direction.x + B * ray.direction.y + C * ray.direction.z),

      x = t * ray.direction.x + ray.origin.x,
      y = t * ray.direction.y + ray.origin.y,
      z = t * ray.direction.z + ray.origin.z;

    Vector ans(x, y, z);
    Vector normal(A, B, C);
    normal = normal.normalize();
    ans.intersects = pointInTriangle(Vector(x, y, z), facet.v[0], facet.v[1], facet.v[2]);
    return { ans, normal };
}

pair<Vector, Vector> Tracer::intersectsRectangle(Vector up, Vector down, Ray &ray)
{
    return { Vector(), Vector() };
}

template <typename T>
void log(T content)
{
  cout << content << endl;
}

template <typename T>
void log(T content[])
{
  for (int i = 0; i < sizeof(T); i++)
  {
    cout << content[i] << " ";
  }
  cout << endl;
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

template <typename T>
bool sign(T value)
{
  return (value > 0) - (value < 0);
}

bool Tracer::pointInTriangle(Vector x, Vector a, Vector b, Vector c) {
    return squareOfTriangle(a, b, c) == squareOfTriangle(x, a, b) +
                                        squareOfTriangle(x, b, c) +
                                        squareOfTriangle(x, a, c);
}

float Tracer::squareOfTriangle(Vector a, Vector b, Vector c) {
    Vector x = b - a, y = c - a;
    return abs(x.cross(y).length()) / 2;
}
