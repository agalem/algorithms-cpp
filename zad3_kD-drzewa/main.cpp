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
    vector<Point> sortedX;
    vector<Point> sortedY;
    vector<Point> result;

    double tab_x[] = {1, 2, 4, 4, 4, 5, 7, 7};
    double tab_y[] = {3, 5, 1, 2, 7, 4, 5, 7};

    int size = sizeof(tab_x)/sizeof(tab_x[0]);
    fillVector(tab_x, tab_y, size, &points);

    sortedX = sortedY = points;
    sort(sortedX.begin(), sortedX.end(), sortX);
    sort(sortedY.begin(), sortedY.end(), sortY);

    Tree *kDtree;
    Area areaToSearch = fillArea(7, 7, 7, 7);

    kDtree = buildTree(points, 0);
    searchArea(kDtree, areaToSearch, result);

    printPoints(result);

    return 0;
}

void printPoints(vector<Point> tab) {
    for(int i=0; i<tab.size(); i++) {
        cout<<"( "<<tab[i].x<<", "<<tab[i].y<<" )\t";
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
    int size = tab.size();
    int half = size/2;

    vector<Point> tabX, tabY;
    tabX = tabY = tab;

    if(size == 1) {

        result->storedPoint = tab[0];
        result->left = NULL;
        result->right = NULL;


    } else if (height % 2 == 0) {

        sort(tabX.begin(), tabX.end(), sortX);

        vector<Point> tabLeftX (tabX.begin(), tabX.begin() + half);
        vector<Point> tabRightX (tabX.begin() + half, tabX.end());

        result->minXLeft = tabX[0].x;
        result->maxXLeft = tabX[half].x;
        result->minXRight = tabX[half + 1].x;
        result->maxXRight = tabX[tabX.size() - 1].x;

        result->sortedBy = 'x';

        height = height + 1;
        result->left = buildTree(tabLeftX, height);
        result->right = buildTree(tabRightX, height);


    } else {
        sort(tabY.begin(), tabY.end(), sortY);

        vector<Point> tabLeftY(tabY.begin(), tabY.begin() + half);
        vector<Point> tabRightY(tabY.begin() + half, tabY.end());

        result->minYBottom = tabY[0].y;
        result->maxYBottom = tabY[half].y;
        result->minYTop = tabY[half + 1].y;
        result->maxYTop = tabY[tabY.size() - 1].y;

        result->sortedBy = 'y';

        height = height + 1;
        result->left = buildTree(tabLeftY, height);
        result->right = buildTree(tabRightY, height);
    }

    return result;
}

vector<Point> searchArea(Tree *tree, Area area, vector<Point> &result) {

    if(tree->left == NULL && tree->right == NULL) {

        if(tree->storedPoint.x >= area.minX &&
           tree->storedPoint.x <= area.maxX &&
           tree->storedPoint.y >= area.minY &&
           tree->storedPoint.y <= area.maxY) {

            result.push_back(tree->storedPoint);
        }

    } else {

        if(tree->left != NULL) {

            if(tree->sortedBy == 'x') {
               //przecina się
               // 1 -> całość w
               // 2 -> "pochłania"
               // 3 -> przecina lewą krawędź
               // 4 -> przecina prawą krawędź
               if((tree->minXLeft >= area.minX && tree->maxXLeft <= area.maxX) ||
                  (tree->minXLeft < area.minX && tree->maxXLeft > area.minX ) ||
                  (tree->minXLeft <= area.minX && tree->maxXLeft >= area.minX) ||
                  (tree->minXLeft <= area.maxX && tree->maxXLeft >= area.maxX)) {

                   searchArea(tree->left, area, result);

               }
            } else if (tree->sortedBy == 'y') {
                if((tree->minYBottom >= area.minY && tree->maxYBottom <= area.maxY) ||
                   (tree->minYBottom < area.minY && tree->maxYBottom > area.maxY) ||
                   (tree->minYBottom < area.maxY && tree->maxYBottom >= area.maxY) ||
                   (tree->minYBottom < area.minY && tree->maxYBottom >= area.minY)) {

                    searchArea(tree->left, area, result);
                }
            }

        }
        if(tree->right != NULL) {
            if(tree->sortedBy == 'x') {
                //przecina się
                // 1 -> całość w
                // 2 -> "pochłania"
                // 3 -> przecina lewą krawędź
                // 4 -> przecina prawą krawędź
                if(((tree->minXRight >= area.minX && tree->maxXRight <= area.maxX) ||
                   (tree->minXRight < area.minX && tree->maxXRight > area.minX ) ||
                   (tree->minXRight <= area.minX && tree->maxXRight >= area.minX) ||
                   (tree->minXRight <= area.maxX && tree->maxXRight >= area.maxX))) {

                    searchArea(tree->right, area, result);
                }
            } else if (tree->sortedBy == 'y') {
                if((tree->minYTop >= area.minY && tree->maxYTop <= area.maxY) ||
                   (tree->minYTop < area.minY && tree->maxYTop > area.maxY) ||
                   (tree->minYTop < area.maxY && tree->maxYTop >= area.maxY) ||
                   (tree->minYTop < area.minY && tree->maxYTop >= area.minY)) {

                    searchArea(tree->right, area, result);
                }
            }
        }
    }

    return result;
}