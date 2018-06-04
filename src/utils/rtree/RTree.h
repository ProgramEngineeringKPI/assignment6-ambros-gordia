#include "../tracer/Tracer.h"

struct Rect {
    bool assigned;
    Vector up, down;

    void blow(Vector v);

    Rect();
};

struct Node {

    Rect bound;
    Node *l, *r;
    vector<Vector> v;

    Node(Rect b, vector<Vector> &origin, int start, int end);
    Node();
};

class RTree {

private:

    Node root;

public:

    void build(vector<Vertex> &v);
};