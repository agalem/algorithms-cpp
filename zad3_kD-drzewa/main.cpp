#include <iostream>
#include <algorithm>
#include <vector>

#include "Area.h"
#include "Tree.h"
#include "Point.h"

using namespace std;

void printPoints(vector<Point> tab);

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec);

Area fillArea(double minX, double maxX, double minY, double maxY);

Tree* buildTree(vector<Point> tab, int height);

vector<Point> searchArea(Tree *tree, Area area, vector<Point> &result);

bool sortX(Point a, Point b) { return a.x < b.x; }
bool sortY(Point a, Point b) { return a.y < b.y; }

int main(void) {
    vector<Point> points;
    vector<Point> result;

    double tab_x[] = {1, 2, 4, 4, 4, 5, 7, 7};
    double tab_y[] = {3, 5, 1, 2, 7, 4, 5, 7};


    int size = sizeof(tab_x)/sizeof(tab_x[0]);
    fillVector(tab_x, tab_y, size, &points);

    Tree *kDtree;
    Area areaToSearch = fillArea(3, 6, 2, 5);

    kDtree = buildTree(points, 0);
    searchArea(kDtree, areaToSearch, result);

    printPoints(result);

    return 0;
}

void printPoints(vector<Point> tab) {
    for(int i=0; i<tab.size(); i++) {
        cout<<"("<<tab[i].x<<","<<tab[i].y<<")\t";
    }
    cout<<endl;
}

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec) {
    Point temp = {0,0};

    for(int i=0; i<size; i++) {
        temp.x = tab1[i];
        temp.y = tab2[i];

        vec->push_back(temp);
    }
}

Area fillArea(double minX, double maxX, double minY, double maxY) {
    Area tempArea;

    tempArea.minX = minX;
    tempArea.maxX = maxX;
    tempArea.minY = minY;
    tempArea.maxY = maxY;

    return tempArea;
}

Tree* buildTree(vector<Point> tab, int height) {
    Tree *result = new Tree;
    result->points = tab;
    int size = tab.size();
    int half = size/2;

    vector<Point> tabX, tabY;
    tabX = tabY = tab;

    if(size == 1) {
        result->dividing = tab[0];
        result->depth = height;
        result->left = NULL;
        result->right = NULL;

        //cout << "Korzeń: x: " << result->dividing.x << "  y: " << result->dividing.y << endl;

    } else if (height % 2 == 0) {

        sort(tabX.begin(), tabX.end(), sortX);
        result->dividing = tabX[half];

        vector<Point> tabLeftX (tabX.begin(), tabX.begin() + half);
        vector<Point> tabRightX (tabX.begin() + half, tabX.end());

        height = height + 1;
        result->depth = height;
        result->left = buildTree(tabLeftX, height);
        result->right = buildTree(tabRightX, height);

    } else {

        sort(tabY.begin(), tabY.end(), sortY);
        result->dividing = tabY[half];

        vector<Point> tabLeftY(tabY.begin(), tabY.begin() + half);
        vector<Point> tabRightY(tabY.begin() + half, tabY.end());

        height = height + 1;
        result->depth = height;
        result->left = buildTree(tabLeftY, height);
        result->right = buildTree(tabRightY, height);
    }

    return result;
}


vector<Point> searchArea(Tree *tree, Area area, vector<Point> &result) {

    if(tree->left == NULL && tree->right == NULL) {

        if(tree->dividing.x >= area.minX &&
           tree->dividing.x <= area.maxX &&
           tree->dividing.y >= area.minY &&
           tree->dividing.y <= area.maxY) {

            result.push_back(tree->dividing);

        }

    } else {
        if(tree->left != NULL) {
            searchArea(tree->left, area, result);
        }
        if(tree->right != NULL) {
            searchArea(tree->right, area, result);
        }
    }

    return result;

}