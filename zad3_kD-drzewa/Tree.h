#ifndef ZAD3_KD_DRZEWA_TREE_H
#define ZAD3_KD_DRZEWA_TREE_H

#include "Point.h"
#include <vector>

using namespace std;

class Tree {
public:
    vector<Point> points;
    Point dividing;
    int depth;
    Tree *left, *right;
};

#endif //ZAD3_KD_DRZEWA_TREE_H
