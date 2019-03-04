#include "Polygon.h"

Polygon::Polygon(std::vector<double > vectorOfX, std::vector<double > vectorOfY) : vectorX(std::move(vectorOfX)), vectorY(std::move(vectorOfY)) {
    this->isAllNucleus = false;
}

int Polygon::checkTurningDirection(int pointIndex) {
    int i = pointIndex;
    double x0, x1, x2, y0, y1, y2;

    std::vector<double > vecX = this->vectorX;
    std::vector<double > vecY = this->vectorY;

    x0 = vecX[i-1];
    x1 = vecX[i];
    x2 = vecX[i+1];
    y0 = vecY[i-1];
    y1 = vecY[i];
    y2 = vecY[i+1];

    if(i == 0) {
        x0 = vecX[vecX.size() - 1];
        y0 = vecY[vecY.size() - 1];
    } else if (i ==  vecX.size() - 1) {
        x2 = vecX[0];
        y2 = vecY[0];
    }

    double compute = ((x2 - x0)*(y1 - y0)) - ((x1-x0)*(y2-y0));
    if(compute > 0 && y0 >= y1 && y1 <= y2 ) {
        //z punktu przechodzimy w prawo, w górę osi y
        return -1;
    } else if (compute > 0 && y0 <= y1 && y1 >= y2) {
        //z punktu przechodzimy w prawo, w dół osi y
        return 1;
    }
    return 0;
}

void Polygon::getMaxAndMinLocal() {
    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    std::vector<double> vecMaxLoc, vecMinLoc;
    std::vector<double>::iterator resultMaxIndex, resultMinIndex;

    double resultMax, resultMin;

    int i;
    for(i=0; i<vecY.size() - 1; i++) {
        if(checkTurningDirection(i) == 1){
            vecMaxLoc.push_back(vecY[i]);
        } else if (checkTurningDirection(i) == -1) {
            vecMinLoc.push_back(vecY[i]);
        }
    }

    if(vecMaxLoc.empty() && vecMinLoc.empty()) {
        this->isAllNucleus = true;
    }

    if(vecMaxLoc.empty()){
        vecMaxLoc = vecY;
        resultMaxIndex = std::min_element(vecMaxLoc.begin(), vecMaxLoc.end());
    } else {
        resultMaxIndex = std::max_element(vecMaxLoc.begin(), vecMaxLoc.end());
    }

    if(vecMinLoc.empty()) {
        vecMinLoc = vecY;
        resultMinIndex = std::max_element(vecMinLoc.begin(), vecMinLoc.end());
    } else {
        resultMinIndex = std::min_element(vecMinLoc.begin(), vecMinLoc.end());
    }

    resultMax = vecMaxLoc[std::distance(vecMaxLoc.begin(), resultMaxIndex)];
    resultMin = vecMinLoc[std::distance(vecMinLoc.begin(), resultMinIndex)];

    this->maxLocal = resultMax;
    this->minLocal = resultMin;
}

int Polygon::checkNucleus() {
    this->getMaxAndMinLocal();
    return this->minLocal >= this->maxLocal;
}

double Polygon::countA(double x1, double x2, double y1, double y2) {
    if((x2 - x1) != 0) {
        return (y2 - y1)/(x2 - x1);
    } else {
        return  0;
    }
}

double Polygon::countB(double x1, double x2, double y1, double y2) {
    return y1 - (this->countA(x1,  x2, y1, y2) * x1);
}

double Polygon::countX(double y, double x1, double x2, double y1, double y2) {
    if(this->countA(x1, x2, y1, y2) != 0) {
        return (y / this->countA(x1, x2, y1, y2)) - (this->countB(x1, x2, y1, y2) / this->countA(x1, x2, y1, y2));
    } else {
        return 0;
    }
}

void Polygon::findTopCornersVectors(std::vector<double> &vectorAllX, std::vector<double> &vectorAllY) {
    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    for(int i=0; i<vecY.size(); i++) {
        if(vecY[i] < this->minLocal &&
           vecY[i+1] > this->minLocal &&
           vecY[i+1] < this->maxLocal &&
           vecY[i+1] > this->maxLocal) {
            vectorAllX.push_back(vecX[i]);
            vectorAllX.push_back(vecX[i+1]);
            vectorAllY.push_back(vecY[i]);
            vectorAllY.push_back(vecY[i+1]);
        } else if(vecY[i] == this->minLocal) {
            vectorAllX.push_back(vecX[i]);
        }
    }
}

void Polygon::setTopRightCornerX() {
    std::vector<double>::iterator it, resultMaxIndex;
    std::vector<double> vectorAllX;
    std::vector<double> vectorAllY;

    this->findTopCornersVectors(vectorAllX, vectorAllY);

    if(!vectorAllX.empty() && vectorAllY.empty()) {
        resultMaxIndex = std::max_element(vectorAllX.begin(), vectorAllX.end());
        this->topRightCornerX = vectorAllX[std::distance(vectorAllX.begin(), resultMaxIndex)];
    }

    std::cout << "Wektor X:" << std::endl;
    for(it = vectorAllX.begin(); it != vectorAllX.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nWektor Y: " << std::endl;
    for(it = vectorAllY.begin(); it != vectorAllY.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\nPrawy górny róg: " << this->topRightCornerX << std::endl;

}

void Polygon::printOutput() {
    if(this->checkNucleus()) {
        std::cout << "Jądro istnieje" << std::endl;
    } else {
        std::cout << "Brak jądra" << std::endl;
    }
    std::cout << "Min lokalne: " << this->minLocal << " Max lokalne: " << this->maxLocal << std::endl;
}