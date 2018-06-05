#include "../tracer/Tracer.hpp"

struct Rect {
    bool assigned;
    Vector up, down;
    
    void blow(Vector &v);
    
    Rect();
    Rect(float ux, float uy, float uz, float dx, float dy, float dz);
};

struct Node {
    
    Rect bound;
    Node *l, *r;
    int lvl;
    vector<Vertex> v;
    
    Node(int lvl, Rect b, vector<Vertex> &origin, float mid, bool over, char mode);
    Node();
};

class RTree {
    
private:
    
    const int MAX_CAPACITY = 10;
    
    Node *root;
    Tracer tracer;
    
    void recursiveBuild(Node *curr);
    
    void destructBy(Node *curr);
    
    char makeDecision(Node *curr);
    
    Node *recursiveSearch(Node *pos, Ray ray);
    
public:
    
    RTree(Tracer t);
    
    void build(vector<Vertex> &v);
    
    //<bool = Result of intersection(false if not intersected, and true vise versa), Vector = normal>
    pair<Vector, Vector> find(Ray ray);
};


