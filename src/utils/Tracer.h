#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Facet;
struct Vertex;

struct Vector
{
    Vector();
    Vector(const float coordinates[3]);
    Vector(std::vector<float> vector);
    float x, y, z;
};

struct Vertex
{
    Vertex(Vector vec, Facet *facet, int facet_count);
    Vector pt;
    Facet *f;
    int facet_count;
};

struct Facet
{
    Vertex *vertices[3];
};

struct Ray
{
    Vector pt, dir; // dir is local vector
};

template <typename T>
void log(T content);

template <typename T>
vector<T> strsplit(string input, char delimiter);

class Tracer
{
  public:
    void parseOBJ(const char *fname, vector<Vertex> &vertices, vector<Facet> &faces);
    bool intersectsTriangle(Facet facet, Ray ray);
    bool intersectsRectangle(Vector up, Vector down, Ray ray);

  private:
    Vector local_to_world(Vector *child, Vector *parent);
    Vector world_to_local(Vector *child, Vector *parent); // child & parent should be in local coords
};
