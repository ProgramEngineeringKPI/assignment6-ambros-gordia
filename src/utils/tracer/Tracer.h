#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

struct Facet;
struct Vertex;

struct Vector
{
    Vector();
    Vector(float X, float Y, float Z);
    Vector(const float coordinates[3]);
    Vector(vector<float> vector);
    float x, y, z;
};

struct Vertex
{
    Vertex();
    Vertex(Vector vec);
    Vector pt;
    vector<Facet> facets;
};

struct Facet
{
    Facet(Vector v1, Vector v2, Vector v3);
    Vector v[3];
};

struct Ray
{
    Vector pt, dir; // dir is local vector
};

template <typename T> void log(T content);

template <typename T> vector<T> strsplit(string input, char delimiter);

class Tracer
{
  public:
    void parseOBJ(const char *fname, vector<Vertex> &vertices, vector<Facet> &faces);

    //<Point of intersection, Normal>
    pair<Vector, Ray> intersectsTriangle(Facet facet, Ray ray);

    pair<Vector, Ray> intersectsRectangle(Vector up, Vector down, Ray ray);

  private:
    Vector local_to_world(Vector *child, Vector *parent);
    Vector world_to_local(Vector *child, Vector *parent); // child & parent should be in local coords
};
