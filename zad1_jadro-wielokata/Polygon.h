//
// Created by Agnieszka Lempaszek on 2019-03-02.
//
#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <cmath>

#ifndef POLYGON_H
#define POLYGON_H


class Polygon {
private:
    double minLocal;
    double maxLocal;
    std::vector<double> vectorX;
    std::vector<double> vectorY;
    bool isAllNucleus;
    double topRightCornerX;
    double topLeftCornerX;
    double bottomRightCornerX;
    double bottomLeftCornerX;
public:
    Polygon(std::vector<double > vectorOfX, std::vector<double> vectorOfY);
    int checkTurningDirection(int pointIndex);
    void getMaxAndMinLocal();
    int checkNucleus();
    double countA(double x1, double x2, double y1, double y2);
    double countB(double x1, double x2, double y1, double y2);
    double countX(double y, double x1, double x2, double y1, double y2);
    void findTopCornersVectors(std::vector<double> &vectorAllX, std::vector<double> &vectorAllY);
    void setTopRightCornerX();
    void printOutput();
};


#endif //POLYGON_H
