#include <cmath>
#include "RTree.h"

Rect::Rect() {
    assigned = false;
}

Rect::Rect(float ux, float uy, float uz, float dx, float dy, float dz): up(Vector(ux, uy, uz)), down(Vector(dx, dy, dz)) {
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

bool cmpX(Vertex v1, Vertex v2) { return v1.pt.x > v2.pt.x; }
bool cmpY(Vertex v1, Vertex v2) { return v1.pt.y > v2.pt.y; }
bool cmpZ(Vertex v1, Vertex v2) { return v1.pt.z > v2.pt.z; }

Node::Node(int LVL, Rect b, vector<Vertex> &origin, int start, int end): bound(b), lvl(LVL), l(nullptr), r(nullptr) {
    for (int i = start; i < end; i++) v.push_back(origin[i]);
}

Node::Node() {
    l = r = nullptr;
    lvl = 0;
}

void RTree::destructBy(Node *curr) {
    float mid;
    char mode = makeDecision(curr);
    if (mode == 'x') {
        sort(curr->v.begin(), curr->v.end(), cmpX);
        mid = curr->v[curr->v.size() / 2].pt.x;
        curr->l = new Node(curr->lvl + 1,
                           Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, mid, curr->bound.down.y, curr->bound.down.z),
                           curr->v,
                           0,
                           curr->v.size() / 2);
        curr->r = new Node(curr->lvl + 1,
                           Rect(mid, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z),
                           curr->v,
                           curr->v.size() / 2,
                           curr->v.size());
    } else if (mode == 'y') {
        sort(curr->v.begin(), curr->v.end(), cmpY);
        mid = curr->v[curr->v.size() / 2].pt.y;
        curr->l = new Node(curr->lvl + 1,
                           Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, mid, curr->bound.down.z),
                           curr->v,
                           0,
                           curr->v.size() / 2);
        curr->r = new Node(curr->lvl + 1,
                           Rect(curr->bound.up.x, mid, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z),
                           curr->v,
                           curr->v.size() / 2,
                           curr->v.size());
    } else if (mode == 'z') {
        sort(curr->v.begin(), curr->v.end(), cmpZ);
        mid = curr->v[curr->v.size() / 2].pt.z;
        curr->l = new Node(curr->lvl + 1,
                           Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, mid),
                           curr->v,
                           0,
                           curr->v.size() / 2);
        curr->r = new Node(curr->lvl + 1,
                           Rect(curr->bound.up.x, curr->bound.up.y, mid, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z),
                           curr->v,
                           curr->v.size() / 2,
                           curr->v.size());
    }
}

char RTree::makeDecision(Node *curr) {
    pair<int, char> dec[3];
    dec[0].second = 'x';
    dec[1].second = 'y';
    dec[2].second = 'z';
    switch (curr->lvl % 3) {
        case 0:
            dec[1].first += 2;
            dec[2].first += 1;
            break;
        case 1:
            dec[0].first += 1;
            dec[2].first += 2;
            break;
        case 2:
            dec[0].first += 2;
            dec[1].first += 1;
    }
    if (curr->bound.down.x == curr->bound.up.x) dec[0].first -= 100;
    if (curr->bound.down.y == curr->bound.up.y) dec[1].first -= 100;
    if (curr->bound.down.z == curr->bound.up.z) dec[2].first -= 100;
    sort(dec, dec + 3);
    return dec[2].second;
}

void RTree::recursiveBuild(Node *curr) {
    if (curr->v.size() < MAX_CAPACITY) return;

    destructBy(curr);

    if (curr->l != nullptr) recursiveBuild(curr->l);
    if (curr->r != nullptr) recursiveBuild(curr->r);
}

void RTree::build(vector<Vertex> &v) {
    root = new Node();
    for (int i = 0; i < v.size(); i++) {
        root->bound.blow(v[i].pt);
        root->v.push_back(v[i].pt);
    }
    recursiveBuild(root);
}