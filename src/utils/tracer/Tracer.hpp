#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <math.h>

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
    
    // operators
    operator bool();
    Vector operator+(Vector &v);
    Vector operator-(Vector &v);
    Vector operator*(float num);
    Vector operator/(float num);
    bool operator==(Vector &v);
    float dot(Vector &v);
    Vector normalize();
    float length();
    Vector cross(Vector &v);
    float angle(Vector &v);
    
    void print();
    bool intersects = false;
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
    Vector n;
};

struct Ray
{
    Ray(Vector _origin, Vector _direction);
    Vector origin, direction; // dir is local vector
};

struct Camera
{
    Vector
    position = Vector(5, 4, 1.5),
    direction = Vector(-1, -0.7, -0.2),
    //            position = Vector(-5, 0, 0),
    //            direction = Vector(1, 0, 0),
    top = Vector(0, 0, 1); // this vector is always lookin' upwards
    int
    resX = 512,
    resY = 512;
    float
    FOV = 60,        // degrees
    FOVmm = 50, // millimeters
    size = 1;
};

template <typename T>
void log(T content);
template <typename T>
void log(T content[]);


float to_rad(float deg);
float to_deg(float rad);

template <typename T>
vector<T> strsplit(string input, char delimiter);

class Tracer
{
public:
    void parseOBJ(const char *fname, vector<Vertex> &vertices, vector<Facet> &faces);
    
    // pair<Vector, Ray> intersectsTriangle(Facet facet, Ray ray); // nope, its not useful
    // pair<Vector, Ray> intersectsBox(Vector up, Vector down, Ray ray);
    pair<Vector, Vector> intersectsTriangle(Facet facet, Ray &ray);
    Vector intersectsBox(Vector up, Vector down, Ray &ray);
    Vector intersectsRect(Vector up, Vector down, Ray &ray);
    Vector intersectsBox2(Vector up, Vector down, Ray &ray);
    
private:
    
    bool pointInTriangle(Vector x, Vector a, Vector b, Vector c);
    
    float squareOfTriangle(Vector a, Vector b, Vector c);
    
};


