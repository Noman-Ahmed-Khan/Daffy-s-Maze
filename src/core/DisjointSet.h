#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

using std::vector;

struct DisjointSet {
    vector<int> parent;
    DisjointSet(int n);
    int find(int x);
    void unite(int x, int y);
};

#endif // DISJOINTSET_H
