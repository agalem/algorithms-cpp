
#pragma once
#include "Point.h"
#include <math.h>

void Point::setX(double inX) {
    this->x = inX;
}

void Point::setY(double inY) {
    this->y = inY;
}

void Point::setHosDist(double dist) {
    this->hosDist = dist;
}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

double Point::getHosDist() {
    return this->hosDist;
}

void Point::printPointData() {
    std::cout << "(" << this->getX() << ", " << this->getY() << "), dist:" << this->getHosDist() << "\n";
}

