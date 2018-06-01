#include "utils/rtree/RTree.h"

int main()
{
    vector<Vertex> verts;
    vector<Facet> faces;
    Tracer tracer;
    RTree tree(tracer);
    tracer.parseOBJ("/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/objects/cube.obj", verts, faces);
    tree.build(verts);
    tree.find(Ray());
}