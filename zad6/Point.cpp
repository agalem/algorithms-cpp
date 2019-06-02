
#pragma once
#include "Point.h"

void Point::setX(double inX) {
    this->x = inX;
}

void Point::setY(double inY) {
    this->y = inY;
}


double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}


void Point::printPointData() {
    std::cout << "(" << this->getX() << ", " << this->getY() << ")" << "\n";
}

