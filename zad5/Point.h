
#pragma once
#ifndef LAB5_SZPITALE_POINT_H
#define LAB5_SZPITALE_POINT_H


class Point {
private:
    double x;
    double y;
    double hosDist;
public:
    void setX(double inX);
    void setY(double inY);
    void setHosDist(double dist);
    double getX();
    double getY();
    double getHosDist();
    void printPointData();
};


#endif
