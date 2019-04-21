#ifndef ZAD3_KD_DRZEWA_TREE_H
#define ZAD3_KD_DRZEWA_TREE_H

#include "Point.h"
#include <vector>

using namespace std;

class Tree {
public:
    Point storedPoint;
    double minXLeft;
    double minXRight;
    double maxXLeft;
    double maxXRight;
    double minYBottom;
    double minYTop;
    double maxYBottom;
    double maxYTop;
    char sortedBy;
    Tree *left, *right;
};


#endif //ZAD3_KD_DRZEWA_TREE_H
