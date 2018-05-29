struct Facet;
struct Vectex;

struct Vector {
    float x, y, z;
};

struct Vertex
{
    Vector pt;
    Facet *f;
    int facet_count;
};

struct Facet
{
    Vertex *a1, *a2, *a3;
};

struct Ray
{
    Vector pt, dir;
};

class Graphics
{

public:

    void parse(const char* fname);

    bool intersectsTriangle(Facet facet, Ray ray);

    bool intersectsRectangle(Vector up, Vector down, Ray ray);

private:

};
