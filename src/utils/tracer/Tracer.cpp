#include "Tracer.hpp"

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
template<typename T> inline T sqr(T t) { return t * t; }

float dist(Vector v1, Vector v2) { return sqrt(sqr(v1.x - v2.x) + sqr(v1.y - v2.y) + sqr(v1.z - v2.z)); }

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

Vector Vector::operator/(float num)
{
    return Vector(x / num, y / num, z / num);
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

float Vector::angle(Vector &v)
{
    return acosf(dot(v) / (length() * v.length()));
}

void Vector::print()
{
    cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vertex::Vertex()
{
}

Vertex::Vertex(Vector &vec)
{
    pt = vec;
}

<<<<<<< HEAD
Vertex::Vertex() {}

Facet::Facet(Vector v1, Vector v2, Vector v3)
=======
Facet::Facet(Vector &v1, Vector &v2, Vector &v3)
>>>>>>> geometry
{
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
}

Ray::Ray() : origin(0, 0, 0), direction(0, 0, 0) {}

Ray::Ray(Vector &_origin, Vector &_direction)
{
    origin = _origin;
    direction = _direction;
}

Light::Light(Vector _position, float _intensity)
{
  position = _position;
  intencity = _intensity;
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
<<<<<<< HEAD
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
=======
          vector<string> coords = strsplit<string>(str, ' ');
          Vector v = Vector(stof(coords[1]), stof(coords[2]), stof(coords[3]));
          vertices.push_back(Vertex(v));
>>>>>>> geometry
        }
    }
    else
    {
        log("Error opening " + (string)fname);
    }
    cout << "Vertex count: " << vertices.size() << "\nFacets count: " << faces.size() << "\n";
}

pair<Vector, Vector> Tracer::intersectsTriangle(Facet &facet, Ray &ray)
{
<<<<<<< HEAD
    //cout<<"#Triangle"<<endl;
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
    
    // Vector ans(x, y, z);
    Vector normal(A, B, C);
    normal = normal.normalize();
    // ans.intersects = pointInTriangle(Vector(x, y, z), facet.v[0], facet.v[1], facet.v[2]);
    
    Vector res(x, y, z);
    Vector edge1 = facet.v[1] - facet.v[0],
    edge2 = facet.v[2] - facet.v[0],
    h = ray.direction.cross(edge2);
    float a = edge1.dot(h);
    if (a > -E && a < E)
        return {res, normal};
    float f = 1 / a;
    Vector s = ray.origin - facet.v[0];
    float u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return {res, normal};
    Vector q = s.cross(edge1);
    float v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return {res, normal};
    float tt = f * edge2.dot(q);
    res.intersects = (tt > E);
    return {res, normal};
=======
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

  Vector normal(A, B, C);
  normal = normal.normalize();

  Vector res(x, y, z);
  Vector edge1 = facet.v[1] - facet.v[0],
         edge2 = facet.v[2] - facet.v[0],
         h = ray.direction.cross(edge2);
  float a = edge1.dot(h);
  if (a > -E && a < E)
    return {res, normal};
  float f = 1 / a;
  Vector s = ray.origin - facet.v[0];
  float u = f * s.dot(h);
  if (u < 0.0 || u > 1.0)
    return {res, normal};
  Vector q = s.cross(edge1);
  float v = f * ray.direction.dot(q);
  if (v < 0.0 || u + v > 1.0)
    return {res, normal};
  float tt = f * edge2.dot(q);
  res.intersects = (tt > E);
  return {res, normal};
}

bool checkTriangle(Vector a, Vector b, Vector c)
{
}

pair<Vector, Vector> Tracer::intersectsRectangle(Vector up, Vector down, Ray &ray)
{
  return {Vector(), Vector()};
>>>>>>> geometry
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

float to_rad(float deg)
{
    return deg * M_PI / 180;
}
float to_deg(float rad)
{
    return rad * 180 / M_PI;
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

Vector Tracer::intersectsBox(Vector up, Vector down, Ray &ray) {
    //cout<<"#Rect"<<endl;
    Vector i, mn;
    float dst = INFINITY;
    
    i = intersectsRect(up, Vector(up.x, down.y, down.z), ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    i = intersectsRect(Vector(up.x, down.y, up.z), down, ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    i = intersectsRect(Vector(up.x, up.y, down.z), down, ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    i = intersectsRect(up, Vector(down.x, up.y, down.z), ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    i = intersectsRect(up, Vector(down.x, down.y, up.z), ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    i = intersectsRect(Vector(down.x, up.y, down.z), down, ray);
    if (i && dist(i, ray.origin) < dst) mn = i;
    
    return mn;
}

Vector Tracer::intersectsRect(Vector up, Vector down, Ray &ray) {
    float k;
    Vector ans;
    if (up.x == down.x) {
        k = (up.x - ray.origin.x) / ray.direction.x;
        ans = Vector(up.x, ray.origin.y + ray.direction.y * k, ray.origin.z + ray.direction.z * k);
        ans.intersects = (ans.z >= down.z && ans.z <= up.z && ans.y >= down.y && ans.y <= up.y);
    } else if (up.y == down.y) {
        k = (up.y - ray.origin.y) / ray.direction.y;
        ans = Vector(ray.origin.x + ray.direction.x * k, up.y, ray.origin.z + ray.direction.z * k);
        ans.intersects = (ans.z >= down.z && ans.z <= up.z && ans.x >= down.x && ans.x <= up.x);
    } else if (up.z == down.z) {
        k = (up.z - ray.origin.z) / ray.direction.z;
        ans = Vector(ray.origin.x + ray.direction.x * k, ray.origin.y + ray.direction.y * k, up.z);
        ans.intersects = (ans.x >= down.x && ans.x <= up.x && ans.y >= down.y && ans.y <= up.y);
    }
    return ans;
}

Vector Tracer::intersectsBox2(Vector up, Vector down, Ray &ray) {
    
    pair<Vector, Vector> res;
    
    res = intersectsTriangle(Facet(up, Vector(up.x, down.y, up.z), Vector(up.x, up.y, down.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(Vector(up.x, down.y, down.z), Vector(up.x, down.y, up.z), Vector(up.x, up.y, down.z)), ray);
    if (res.first)
        return res.first;
    
    res = intersectsTriangle(Facet(Vector(down.x, down.y, up.z), down, Vector(up.x, down.y, down.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(Vector(down.x, down.y, up.z), Vector(up.x, down.y, up.z), Vector(up.x, down.y, down.z)), ray);
    if (res.first)
        return res.first;
    
    res = intersectsTriangle(Facet(down, Vector(up.x, up.y, down.z), Vector(up.x, down.y, down.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(down, Vector(up.x, up.y, down.z), Vector(down.x, up.y, down.z)), ray);
    if (res.first)
        return res.first;
    
    res = intersectsTriangle(Facet(Vector(down.x, down.y, up.z), up, Vector(up.x, down.y, up.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(Vector(down.x, down.y, up.z), up, Vector(down.x, up.y, up.z)), ray);
    if (res.first)
        return res.first;
    
    res = intersectsTriangle(Facet(Vector(up.x, up.y, down.z), Vector(down.x, up.y, up.z), Vector(down.x, up.y, down.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(Vector(up.x, up.y, down.z), Vector(down.x, up.y, up.z), up), ray);
    if (res.first)
        return res.first;
    
    res = intersectsTriangle(Facet(down, Vector(down.x, down.y, up.z), Vector(down.x, up.y, up.z)), ray);
    if (res.first)
        return res.first;
    res = intersectsTriangle(Facet(down, Vector(down.x, up.y, down.z), Vector(down.x, up.y, up.z)), ray);
    if (res.first)
        return res.first;
    
    return Vector();
}

