#include <iostream>
#include <vector>
#include <math.h>
#include "Point.cpp"

using namespace std;

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec);
double calculateR(vector<Point> points, Point lastHospital);
void findHospitals(int hospitalsNum, vector<Point>* points, vector<Point>* hospitals);
double calculateDistance(Point a, Point b);
void printAllPoints(vector<Point> points);
void printDetailedData(vector<Point> points);

double algorithmTSP(vector<Point>points);

int main() {

    int hospitalsNum = 0;
    Point firstHospital;

    double tab1[] = {5, 1, 7, 2.2, 4};
    double tab2[] = {2, 2, 6.5, 1, 2.6};

    int size = sizeof(tab1)/sizeof(tab1[0]);

    vector<Point> points;
    fillVector(tab1, tab2, size, &points);

    vector<Point> hospitals;

    cout << "Podaj liczbę szpitali:";
    cin >> hospitalsNum;

    if(hospitalsNum < 1) {
        cout << "Liczba szpitali musi być większa niż 1";
        return -1;
    } else if (hospitalsNum == size) {
        hospitals = points;
        points.clear();
    } else {
        firstHospital = points[0];
        cout << "\nSZPITAL: (" << firstHospital.getX() << ", " << firstHospital.getY() << ")\n";

        hospitals.push_back(firstHospital);
        points.erase(points.begin());
        findHospitals(hospitalsNum, &points, &hospitals);
    }


    cout << "\n\nKońcowe lokalizacje szpitali: " << "\n";
    printAllPoints(hospitals);

    Point lastHospital = hospitals.at(hospitals.size() - 1);
    double r = calculateR(points, lastHospital);
    cout << "\nR: " << r << endl;

    return 0;
}

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec){
    Point temp;

    for(int i=0; i<size; i++) {
        temp.setX(tab1[i]);
        temp.setY(tab2[i]);
        vec->push_back(temp);
    }
}

double calculateR(vector<Point> points, Point lastHospital) {
    double r = 0.0;
    for(int i=0; i<points.size(); i++) {
        Point currentPoint = points.at(i);
        double distToHospital = calculateDistance(currentPoint, lastHospital);
        double currentPointDistance = currentPoint.getHosDist();
        if(max(currentPointDistance, distToHospital) > r) {
            r = currentPointDistance;
        }
    }
    return r;
}


void findHospitals(int hospitalsNum, vector<Point>* points, vector<Point>* hospitals) {

    for(int i = 0; i < hospitalsNum - 1; i++) {
        Point furthestPoint;
        int furthestPointIndex = 0;
        double furthestDistance = 0;

        for(int j = 0; j < points->size(); j++) {

            Point* currentPoint = &points->at(j);
            double currentPointDistance = currentPoint->getHosDist();
            Point lastHospital = hospitals->at(hospitals->size() - 1);

            double distToHospital = calculateDistance(*currentPoint, lastHospital);

            if(currentPointDistance != 0.0) {
                currentPoint->setHosDist(min(currentPointDistance, distToHospital));
            } else {
                currentPoint->setHosDist(distToHospital);
            }

            if(distToHospital > furthestDistance) {
                furthestDistance = distToHospital;
                furthestPoint = *currentPoint;
                furthestPointIndex = j;
            }
        }

        printDetailedData(*points);
        cout << "\nSZPITAL: (" << furthestPoint.getX() << ", " << furthestPoint.getY() << ")\n";

        hospitals->push_back(furthestPoint);
        points->erase(points->begin() + furthestPointIndex);
    }
}


double calculateDistance(Point a, Point b) {
    double x1 = a.getX();
    double x2 = b.getX();
    double y1 = a.getY();
    double y2 = b.getY();
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void printAllPoints(vector<Point> points) {
    for(int i=0; i<points.size(); i++) {
        Point point = points.at(i);
        cout << "(" << point.getX() << ", " << point.getY() << "), " << "\n";
    }
}

void printDetailedData(vector<Point> points) {
    cout << "\n\nPunkty:" << endl;
    for(int i=0; i<points.size(); i++) {
        Point point = points.at(i);
        cout << "(" << point.getX() << ", " << point.getY() << "), odległość: " << point.getHosDist() <<"\n";
    }
}