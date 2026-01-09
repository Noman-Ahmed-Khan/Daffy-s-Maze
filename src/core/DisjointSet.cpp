#include "DisjointSet.h"

DisjointSet::DisjointSet(int n) : parent(n) {
    for (int i = 0; i < n; ++i) parent[i] = i;
}

int DisjointSet::find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void DisjointSet::unite(int x, int y) {
    parent[find(x)] = find(y);
}
