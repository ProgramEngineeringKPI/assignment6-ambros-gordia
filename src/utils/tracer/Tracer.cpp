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

Vector Tracer::intersectsTriangle(Facet &facet, Ray &ray)
{
  const float E = 1e-5;
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

  Vector res(x, y, z);
  Vector edge1 = facet.v[1] - facet.v[0],
         edge2 = facet.v[2] - facet.v[0],
         h = ray.direction.cross(edge2);
  float a = edge1.dot(h);
  if (a > -E && a < E)
    return res;

  float f = 1 / a;
  Vector s = ray.origin - facet.v[0];
  float u = f * s.dot(h);
  if (u < 0.0 || u > 1.0)
    return res;
  Vector q = s.cross(edge1);
  float v = f * ray.direction.dot(q);
  if (v < 0.0 || u + v > 1.0)
    return res;
  float tt = f * edge2.dot(q);
  res.intersects = (tt > E);
  return res;
}

Vector Tracer::intersectsRectangle(Vector up, Vector down, Ray &ray)
{
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

void Tracer::Render(const char *input_file, string output_file)
{
  vector<Vertex> vertices;
  vector<Facet> faces;
  parseOBJ(input_file, vertices, faces);
  ofstream out(output_file, ios::binary);

  // file header
  unsigned short width = 512;
  unsigned short height = 512;
  unsigned short colorBit = 3;
  unsigned int size = width * height * colorBit;
  unsigned int offset = 27;
  unsigned int shit = 12;
  unsigned short filehead[4] = {width, height, 1, (unsigned short)(colorBit * 8)};

  out << "BM";
  out.write((char *)&size, sizeof(size));
  out.seekp(4, ios::cur);
  out.write((char *)&offset, sizeof(offset));
  out.write((char *)&shit, sizeof(shit));
  out.write((char *)&filehead, 12);
  out.seekp(offset, ios::beg);

  Vector plane_origin = Vector(main_camera.direction.normalize() + main_camera.position);

  char *buf = new char[size];

  for (int y = 0; y < main_camera.resY; y++)
  {
    for (int x = 0; x < main_camera.resX; x++)
    {
      float
          xNorm = (x - main_camera.resX / 2) / (float)main_camera.resX,
          yNorm = (y - main_camera.resY / 2) / (float)main_camera.resY,
          dist_to_plane = (main_camera.position - plane_origin).length(),
          FOVrad = main_camera.FOV / 180.f * M_PI,
          realH = (float)(dist_to_plane * tanf(FOVrad));
      Vector
          position_on_plane = Vector(xNorm * realH / 2, yNorm * realH / 2, 0) + plane_origin,
          rayDir = position_on_plane - main_camera.position;

      Ray ray = Ray(main_camera.position, rayDir);
      int i = 0;
      for (; i < faces.size(); i++)
      {
        Vector v = intersectsTriangle(faces[i], ray);
        if (v)
        {
          float dist = (v - main_camera.position).length();
          *(buf + (y * height + x) * colorBit + 1) = (char)(dist * 0xFF);
          break;
        }
      }
      if (i >= faces.size())
      {
        *(buf + (y * height + x) * colorBit) = (char)0x0F;
      }
    }
  }
  out.write(buf, sizeof(buf) * 512 * 512);
  out.close();
}
void Tracer::Render(const char *input_file, string output_file, Camera &camera)
{
  main_camera = camera;
  Render(input_file, output_file);
}
