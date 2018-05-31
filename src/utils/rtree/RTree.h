#include "../tracer/Tracer.h"

struct Rect {
    bool assigned;
    Vector up, down;

    void blow(Vector v);

    Rect();
    Rect(float ux, float uy, float uz, float dx, float dy, float dz);
};

struct Node {

    Rect bound;
    Node *l, *r;
    int lvl;
    vector<Vertex> v;

    Node(int lvl, Rect b, vector<Vertex> &origin, int start, int end);
    Node();
};

class RTree {

private:

    const int MAX_CAPACITY = 2;

    Node *root;

    void recursiveBuild(Node *curr);

    void destructBy(Node *curr);

    char makeDecision(Node *curr);

public:

    void build(vector<Vertex> &v);
};