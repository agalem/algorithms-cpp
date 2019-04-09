#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>


#include "Point.h"
#include "Segment.h"

using namespace std;

void createVector(const double *arr1, const double *arr2, int size, vector<Point> *vec);

bool sortByX(Point a, Point b);
bool sortByY(Point a, Point b);
double getDistance(Point a, Point b);
void fillFunc(double[]);

Segment comparePointsDistance(vector<Point> pointsVec);
Segment findNearestPoints(vector<Point> pointsVec, vector<Point> tabX, vector<Point> tabY);

int main() {

    vector<Point> pointsVec, setX, setY;
    vector<Segment> allResults;
    Segment result;

    int size = 1005;

    double arrX[size];
    double arrY[size];

    double j;

    for(int i=0; i<=1000; i++) {
        j = double(i) / 100;
        //cout << j << " ";
        arrX[i] = 200.0 + j;
        arrY[i] = 100.0 * i;
    }
    cout << "\n\n";

    arrX[1001] = 0;
    arrX[1002] = 100;
    arrX[1003] = 1300;
    arrX[1004] = 1400;

    arrY[1001] = 0;
    arrY[1002] = 0;
    arrY[1003] = 0;
    arrY[1004] = 0;




    //double arrX[] = {-6, -5, -3, 1, 5, 7, 8};
    //double arrY[] = {4, -3, 7, 1, -7, 6, -2};


    int sizeVec = sizeof(arrX) / sizeof(arrX[0]);

    createVector(arrX, arrY, sizeVec, &pointsVec);

    setX = pointsVec;
    setY = pointsVec;

    sort(setX.begin(), setX.end(), sortByX);
    sort(setY.begin(), setY.end(), sortByY);

    result = findNearestPoints(pointsVec, setX, setY);

    cout<<"Najbliższe punkty: ";
    cout<< result.a.x<<", "<< result.a.y << " oraz " <<result.b.x << ", "<< result.b.y << endl;
    cout<<"Odległość między nimi: "<< result.distance << endl;

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
                //na lewo od prostej l
                tabYLeft.push_back(tabY[i]);
            } else {
                //na prawo od prostej l
                tabYRight.push_back(tabY[i]);
            }
        }

        Segment leftSegment = findNearestPoints(pointsVecLeft, tabXLeft, tabYLeft);
        Segment rightSegment = findNearestPoints(pointsVecRight, tabXRight, tabYRight);

        double distInLeftSegment = getDistance(leftSegment.a, leftSegment.b);
        double distInRightSegment = getDistance(rightSegment.a, rightSegment.b);

        double dist = min(distInLeftSegment, distInRightSegment);

        vector<Point> smallerY;

        for(int i=0; i<size; i++) {
            if((tabY[i].x > tabX[middle].x-dist) && (tabY[i].x < tabX[middle].x+dist)) {
                smallerY.push_back(tabY[i]);
            }
        }

        for(int i=0; i<size-1; i++) {
            for (int j = i+1; j<size; j++) {
                if(smallerY[j].y - smallerY[i].y < dist) {
                    temp.a = smallerY[i];
                    temp.b = smallerY[j];
                    if (getDistance(smallerY[i], smallerY[j]) < dist) {
                        result = temp;
                        result.distance = getDistance(smallerY[i], smallerY[j]);
                    }
                } else {
                    break;
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