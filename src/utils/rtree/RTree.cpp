#include <cmath>
#include "RTree.h"

Rect::Rect() {
    assigned = false;
}

void Rect::blow(Vector v) {
    if (!assigned) {
        assigned = true;
        up = down = v;
    } else {
        up.x = max(up.x, v.x);
        up.y = max(up.y, v.y);
        up.z = max(up.z, v.z);
        down.x = min(down.x, v.x);
        down.y = min(down.y, v.y);
        down.z = min(down.z, v.z);
    }
}

Node::Node(Rect b, vector<Vector> &origin, int start, int end): bound(b) {
    for (int i = start; i < end; i++) v.push_back(origin[i]);
    l = r = nullptr;
}

Node::Node() {
    l = r = nullptr;
}

void RTree::build(vector<Vertex> &v) {
    for (int i = 0; i < v.size(); i++) root.bound.blow(v[i].pt);
}