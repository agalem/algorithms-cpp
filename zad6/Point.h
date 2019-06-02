#ifndef ZAD6_POINT_H
#define ZAD6_POINT_H
#pragma once

class Point {
private:
    double x;
    double y;
public:
    void setX(double inX);
    void setY(double inY);
    double getX();
    double getY();
    void printPointData();
};


#endif //ZAD6_POINT_H
