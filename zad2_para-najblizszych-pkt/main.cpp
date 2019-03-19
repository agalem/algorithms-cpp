#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Point.h"
#include "Segment.h"

using namespace std;

void createVector(const double *arr1, const double *arr2, int size, vector<Point> *vec);

bool sortByX(Point a, Point b);
bool sortByY(Point a, Point b);
double getDistance(Point a, Point b);

Segment comparePointsDistance(vector<Point> pointsVec);
Segment findNearestPoints(vector<Point> pointsVec, vector<Point> tabX, vector<Point> tabY);

int main() {

    vector<Point> pointsVec, setX, setY;
    vector<Point>::iterator i;
    vector<Segment> allResults;
    Segment result;

    double arrX[] = {-6, -5, -3, 1, 5, 7, 8};
    double arrY[] = {4, -3, 7, 1, -7, 6, -2};

    int size = sizeof(arrX) / sizeof(arrX[0]);

    createVector(arrX, arrY, size, &pointsVec);

    setX = pointsVec;
    setY = pointsVec;

    sort(setX.begin(), setX.end(), sortByX);
    sort(setY.begin(), setY.end(), sortByY);

    result = findNearestPoints(pointsVec, setX, setY);

    cout<<"Najblizej lezace punkty: ";
    cout<<"("<<result.a.x<<","<<result.a.y<<") - ("<<result.b.x<<","<<result.b.y<<")"<<endl;
    cout<<"Odleglosc miedzy nimi wynosi: "<<getDistance(result.a, result.b)<<endl;

    return 0;
}

void createVector(const double *arr1, const double *arr2, int size, vector<Point> *vec) {
    Point initial = {0, 0};

    for(int i=0; i<size; i++) {
        initial.x = arr1[i];
        initial.y = arr2[i];

        vec->push_back(initial);
    }
}

bool sortByX(Point a, Point b) {
    return a.x < b.x;
}

bool sortByY(Point a, Point b) {
    return a.y < b.y;
}

double getDistance(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

Segment comparePointsDistance(vector<Point> pointsVec) {
    int size = pointsVec.size();
    double min = INFINITY;

    Segment temp = {{0,0}, {0,0}};
    Segment result = {{0,0}, {0,0}};

   int i, j;
   for(i = 0; i < size-1; i++) {
       for(j= i+1; j<size; j++) {
           temp.a = pointsVec[i];
           temp.b = pointsVec[j];

           if(getDistance(temp.a, temp.b) < min) {
               min = getDistance(temp.a, temp.b);
               result.a = temp.a;
               result.b = temp.b;
               result.distance = min;
           }
       }
   }

   return result;
}

Segment findNearestPoints(vector<Point> pointsVec, vector<Point> tabX, vector<Point> tabY) {

    int size = pointsVec.size();

    Segment result = {{0,0},{0,0}};
    Segment temp = {{0,0},{0,0}};


    if(size <= 3) {
        return comparePointsDistance(pointsVec);
    } else {
        int middle = size/2;

        vector<Point> pointsVecLeft(pointsVec.begin(), pointsVec.begin() + middle);
        vector<Point> pointsVecRight(pointsVec.begin() + middle, pointsVec.end());

        vector<Point> tabXLeft(tabX.begin(), tabX.begin() + middle);
        vector<Point> tabXRight(tabX.begin() + middle, tabX.end());

        vector<Point> tabYLeft;
        vector<Point> tabYRight;

        for(int i=0; i<size; i++) {
            if(tabY[i].x < tabX[middle].x) {
                tabYLeft.push_back(tabY[i]);
            } else {
                tabYRight.push_back(tabY[i]);
            }
        }

        Segment leftSegment = findNearestPoints(pointsVecLeft, tabXLeft, tabYLeft);
        Segment rightSegment = findNearestPoints(pointsVecRight, tabXRight, tabYRight);

        double distInLeftSegment = getDistance(leftSegment.a, leftSegment.b);
        double distInRightSegment = getDistance(rightSegment.a, rightSegment.b);

        double dist = min(distInLeftSegment, distInRightSegment);


        vector<Point> lineY;

        for(int i=0; i<size; i++) {
            if((tabY[i].x > tabX[middle].x-dist) && (tabY[i].x < tabX[middle].x+dist)) {
                lineY.push_back(tabY[i]);
            }
        }

        for(int i=0; i<size-1; i++) {
            for (int j = i+1; j<size && (lineY[j].y - lineY[i].y) < dist; j++) {
                temp.a = lineY[i];
                temp.b = lineY[j];
                if (getDistance(lineY[i], lineY[j]) < dist) {
                    result = temp;
                    result.distance = getDistance(lineY[i], lineY[j]);
                }
            }
        }

        if(dist == distInLeftSegment) {

            if(result.distance >= dist) {
                return result;
            } else {
                return leftSegment;
            }

        } else if(dist == distInRightSegment) {

            if(result.distance >= dist) {
                return result;
            } else {
                return rightSegment;
            }

        }

        return result;

    }

}