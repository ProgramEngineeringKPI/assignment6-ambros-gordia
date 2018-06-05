#include "RTree.hpp"

bool cmpX(Vertex v1, Vertex v2) { return v1.pt.x > v2.pt.x; }
bool cmpY(Vertex v1, Vertex v2) { return v1.pt.y > v2.pt.y; }
bool cmpZ(Vertex v1, Vertex v2) { return v1.pt.z > v2.pt.z; }

template<typename T> inline T sqr(T t) { return t * t; }

float distFun(Vector v1, Vector v2) { return sqrt(sqr(v1.x - v2.x) + sqr(v1.y - v2.y) + sqr(v1.z - v2.z)); }

Rect::Rect() {
    assigned = false;
}

Rect::Rect(float ux, float uy, float uz, float dx, float dy, float dz): up(Vector(ux, uy, uz)), down(Vector(dx, dy, dz)) {
    assigned = false;
}

void Rect::blow(Vector &v) {
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

Node::Node(int LVL, Rect b, vector<Vertex> &origin, float mid, bool over, char mode): bound(b), lvl(LVL), l(nullptr), r(nullptr) {
    for (int i = 0; i < origin.size(); i++) {
        if (mode == 'x') {
            if ((over && origin[i].pt.x >= mid) || (!over && origin[i].pt.x <= mid)) v.push_back(origin[i]);
        } else if (mode == 'y') {
            if ((over && origin[i].pt.y >= mid) || (!over && origin[i].pt.y <= mid)) v.push_back(origin[i]);
        } else if (mode == 'z') {
            if ((over && origin[i].pt.z >= mid) || (!over && origin[i].pt.z <= mid)) v.push_back(origin[i]);
        }
    }
}

Node::Node() {
    l = r = nullptr;
    lvl = 0;
}

RTree::RTree(Tracer t): tracer(t) {}

void RTree::destructBy(Node *curr) {
    float mid;
    Rect l, r;
    char mode = makeDecision(curr);
    if (mode == 'x') {
        sort(curr->v.begin(), curr->v.end(), cmpX);
        mid = curr->v[curr->v.size() / 2].pt.x;
        l = Rect(mid, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z);
        r = Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, mid, curr->bound.down.y, curr->bound.down.z);
    } else if (mode == 'y') {
        sort(curr->v.begin(), curr->v.end(), cmpY);
        mid = curr->v[curr->v.size() / 2].pt.y;
        l = Rect(curr->bound.up.x, mid, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z);
        r = Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, mid, curr->bound.down.z);
    } else {
        sort(curr->v.begin(), curr->v.end(), cmpZ);
        mid = curr->v[curr->v.size() / 2].pt.z;
        l = Rect(curr->bound.up.x, curr->bound.up.y, mid, curr->bound.down.x, curr->bound.down.y, curr->bound.down.z);
        r = Rect(curr->bound.up.x, curr->bound.up.y, curr->bound.up.z, curr->bound.down.x, curr->bound.down.y, mid);
    }
    
    curr->l = new Node(curr->lvl + 1,
                       l,
                       curr->v,
                       mid,
                       false,
                       mode);
    curr->r = new Node(curr->lvl + 1,
                       r,
                       curr->v,
                       mid,
                       true,
                       mode);
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

Node* RTree::recursiveSearch(Node *pos, Ray ray) {
    if (pos->l == nullptr && pos->r == nullptr) return pos;
    if (pos->l == nullptr) {
        if (tracer.intersectsBox((pos->l)->bound.up, (pos->l)->bound.down, ray)) return recursiveSearch(pos->l, ray);
        return pos;
    }
    if (pos->r == nullptr) {
        if (tracer.intersectsBox((pos->r)->bound.up, (pos->r)->bound.down, ray)) return recursiveSearch(pos->r, ray);
        return pos;
    }
    Vector resL = tracer.intersectsBox((pos->l)->bound.up, (pos->l)->bound.down, ray),
    resR = tracer.intersectsBox((pos->r)->bound.up, (pos->r)->bound.down, ray);
    if (resL && resR) {
        float distL = distFun(ray.origin, resL),
        distR = distFun(ray.origin, resR);
        if (distL < distR) return recursiveSearch(pos->l, ray);
        else return recursiveSearch(pos->r, ray);
    } else if (resL && !resR) return recursiveSearch(pos->l, ray);
    else if (!resL && resR) return recursiveSearch(pos->r, ray);
    
    return pos;
}

void RTree::build(vector<Vertex> &v) {
    root = new Node();
    Vertex vx;
    for (int i = 0; i < v.size(); i++) {
        root->bound.blow(v[i].pt);
        vx = v[i];
        vx.facets.clear();
        for (int j = 0; j < v[i].facets.size(); j++) vx.facets.push_back(v[i].facets[j]);
        root->v.push_back(vx);
    }
    recursiveBuild(root);
}

pair<Vector, Vector> RTree::find(Ray ray) {
    pair<Vector, Vector> ans;
    
    if (!tracer.intersectsBox(root->bound.up, root->bound.down, ray)) return ans;
    
    Node *result = recursiveSearch(root, ray);
    
    float mnDist = INFINITY;
    for (int i = 0; i < result->v.size(); i++)
        for (int j = 0; j < result->v[i].facets.size(); j++) {
            pair<Vector, Vector> inter = tracer.intersectsTriangle(result->v[i].facets[j], ray);
            if (inter.first && mnDist > distFun(ray.origin, inter.first)) {
                mnDist = distFun(ray.origin, inter.first);
                ans.first.intersects = true;
                ans = inter;
            }
        }
    
    if (mnDist == INFINITY) {
        result = root;
        for (int i = 0; i < result->v.size(); i++)
            for (int j = 0; j < result->v[i].facets.size(); j++) {
                pair<Vector, Vector> inter = tracer.intersectsTriangle(result->v[i].facets[j], ray);
                if (inter.first && mnDist > distFun(ray.origin, inter.first)) {
                    mnDist = distFun(ray.origin, inter.first);
                    ans.first.intersects = true;
                    ans = inter;
                }
            }
    }
    
    return ans;
}

