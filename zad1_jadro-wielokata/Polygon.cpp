#include "Polygon.h"

Polygon::Polygon(std::vector<double > vectorOfX, std::vector<double > vectorOfY) : vectorX(std::move(vectorOfX)), vectorY(std::move(vectorOfY)) {}

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
    if(compute > 0 && y0 > y1 && y1 < y2 ) {
        //z punktu przechodzimy w prawo, w górę osi y
        return -1;
    } else if(compute >  0 && y0 > y1 && y1 == y2) {
        return -2;
    } else if (compute > 0 && y0 < y1 && y1 > y2) {
        //z punktu przechodzimy w prawo, w dół osi y
        return 1;
    } else if(compute > 0 && y0 < y1 && y1 == y2) {
        return 2;
    }
    return 0;
}

void Polygon::getMaxAndMinLocal() {
    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    std::vector<double> vecMaxLoc, vecMinLoc;
    std::vector<double>::iterator resultMaxIndex, resultMinIndex;

    double resultMax, resultMin;

    int i, j;
    for(i=0; i<vecY.size() - 1; i++) {
        if(checkTurningDirection(i) == 1){
            vecMaxLoc.push_back(vecY[i]);
        } else if(checkTurningDirection(i) == 2) {
            vecY.push_back(vecY.front());
            for(j=i; j<vecY.size() - 2; j++) {
                if(vecY[j+1] < vecY[j]) {
                    vecMaxLoc.push_back(vecY[j]);
                }
            }
        } else if (checkTurningDirection(i) == -1) {
            vecMinLoc.push_back(vecY[i]);
        } else if (checkTurningDirection(i) == -2) {
            vecY.push_back(vecY.front());
            for(j = i; j<vecY.size() - 2; j++) {
                if(vecY[j+1] > vecY[j]) {
                    vecMinLoc.push_back(vecY[j]);
                }
            }
        }
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
//    std::cout << "x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << std::endl;
    if((y2 - y1) != 0 && (x2 - x1) == 0 ) {
        return x1;
    }
    if(this->countA(x1, x2, y1, y2) != 0) {
        return (y / this->countA(x1, x2, y1, y2)) - (this->countB(x1, x2, y1, y2) / this->countA(x1, x2, y1, y2));
    } else {
        return 0;
    }
}

void Polygon::setTopRightCornerX() {
    std::vector<double>::iterator it, resultMaxIndex;
    std::vector<double> vectorAllX;
    std::vector<double> vectorAllY;

    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    vecX.push_back(vecX[0]);
    vecY.push_back(vecY[0]);

    for(int i=0; i<vecY.size(); i++) {
        if(vecY[i] < this->minLocal && vecY[i+1] == this->minLocal) {
            vectorAllX.push_back(vecX[i+1]);
        } else if (vecY[i] < this->minLocal && vecY[i+1] > this->minLocal) {
            vectorAllX.push_back(vecX[i]);
            vectorAllX.push_back(vecX[i+1]);
            vectorAllY.push_back(vecY[i]);
            vectorAllY.push_back(vecY[i+1]);
        }
    }
//
//    this->findTopCornersVectors(vectorAllX, vectorAllY);
//
    if(!vectorAllX.empty() && vectorAllY.empty()) {
        resultMaxIndex = std::max_element(vectorAllX.begin(), vectorAllX.end());
        this->topRightCornerX = vectorAllX[std::distance(vectorAllX.begin(), resultMaxIndex)];
    } else {
        this->topRightCornerX = this->countX(this->minLocal, vectorAllX.front(), vectorAllX.back(), vectorAllY.front(), vectorAllY.back());
    }

//    std::cout << "Wektor X:" << std::endl;
//    for(it = vectorAllX.begin(); it != vectorAllX.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y: " << std::endl;
//    for(it = vectorAllY.begin(); it != vectorAllY.end(); ++it) {
//        std::cout << *it << " ";
//    }
//
//
//
 std::cout << "\nPrawy górny róg: " << this->topRightCornerX << std::endl;

}

void Polygon::setTopLeftCornerX() {
    std::vector<double>::iterator it, resultMinIndex;
    std::vector<double> vectorAllX;
    std::vector<double> vectorAllY;

    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    vecX.push_back(vecX[0]);
    vecY.push_back(vecY[0]);

    for(int i=0; i<vecY.size(); i++) {
        if(vecY[i] == this->minLocal && vecY[i+1] < this->minLocal) {
            vectorAllX.push_back(vecX[i]);
        } else if (vecY[i] > this->minLocal && vecY[i+1] < this->minLocal) {
            vectorAllX.push_back(vecX[i]);
            vectorAllX.push_back(vecX[i+1]);
            vectorAllY.push_back(vecY[i]);
            vectorAllY.push_back(vecY[i+1]);
        }
    }

    if(!vectorAllX.empty() && vectorAllY.empty()) {
        resultMinIndex = std::min_element(vectorAllX.begin(), vectorAllX.end());
        this->topLeftCornerX = vectorAllX[std::distance(vectorAllX.begin(), resultMinIndex)];
    } else {
        this->topLeftCornerX = this->countX(this->minLocal, vectorAllX.front(), vectorAllX.back(), vectorAllY.front(), vectorAllY.back());
    }

//
//    std::cout << "Wektor X:" << std::endl;
//    for(it = vectorAllX.begin(); it != vectorAllX.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y: " << std::endl;
//    for(it = vectorAllY.begin(); it != vectorAllY.end(); ++it) {
//        std::cout << *it << " ";
//    }
//
    std::cout << "\nLewy górny róg: " << this->topLeftCornerX << std::endl;

}


void Polygon::setBottomLeftCornerX() {
    std::vector<double>::iterator it, resultMinIndex;
    std::vector<double> vectorAllX;
    std::vector<double> vectorAllY;

    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    vecX.push_back(vecX[0]);
    vecY.push_back(vecY[0]);

    for(int i=0; i<vecY.size(); i++) {
        if(vecY[i] > this->maxLocal && vecY[i+1] == this->maxLocal) {
            vectorAllX.push_back(vecX[i+1]);
        } else if (vecY[i] > this->maxLocal && vecY[i+1] < this->maxLocal) {
            vectorAllX.push_back(vecX[i]);
            vectorAllX.push_back(vecX[i+1]);
            vectorAllY.push_back(vecY[i]);
            vectorAllY.push_back(vecY[i+1]);
        }
    }

    if(!vectorAllX.empty() && vectorAllY.empty()) {
        resultMinIndex = std::min_element(vectorAllX.begin(), vectorAllX.end());
        this->bottomLeftCornerX = vectorAllX[std::distance(vectorAllX.begin(), resultMinIndex)];
    } else {
        this->bottomLeftCornerX = this->countX(this->maxLocal, vectorAllX.front(), vectorAllX.back(), vectorAllY.front(), vectorAllY.back());
    }

//    std::cout << "Wektor X:" << std::endl;
//    for(it = vectorAllX.begin(); it != vectorAllX.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y: " << std::endl;
//    for(it = vectorAllY.begin(); it != vectorAllY.end(); ++it) {
//        std::cout << *it << " ";
//    }
//
    std::cout << "\nLewy dolny róg: " << this->bottomLeftCornerX << std::endl;

}

void Polygon::setBottomRightCornerX() {
    std::vector<double>::iterator it, resultMinIndex;
    std::vector<double> vectorAllX;
    std::vector<double> vectorAllY;

    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;

    vecX.push_back(vecX[0]);
    vecY.push_back(vecY[0]);

    for(int i=0; i<vecY.size(); i++) {
        if(vecY[i] == this->maxLocal && vecY[i+1] > this->maxLocal) {
            vectorAllX.push_back(vecX[i]);
        } else if (vecY[i] < this->maxLocal && vecY[i+1] > this->maxLocal) {
            vectorAllX.push_back(vecX[i]);
            vectorAllX.push_back(vecX[i+1]);
            vectorAllY.push_back(vecY[i]);
            vectorAllY.push_back(vecY[i+1]);
        }
    }

    if(!vectorAllX.empty() && vectorAllY.empty()) {
        resultMinIndex = std::max_element(vectorAllX.begin(), vectorAllX.end());
        this->bottomRightCornerX = vectorAllX[std::distance(vectorAllX.begin(), resultMinIndex)];
    } else {
        this->bottomRightCornerX = this->countX(this->maxLocal, vectorAllX.front(), vectorAllX.back(), vectorAllY.front(), vectorAllY.back());
    }

//    std::cout << "Wektor X:" << std::endl;
//    for(it = vectorAllX.begin(); it != vectorAllX.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y: " << std::endl;
//    for(it = vectorAllY.begin(); it != vectorAllY.end(); ++it) {
//        std::cout << *it << " ";
//    }
//
    std::cout << "\nPrawy dolny róg: " << this->bottomRightCornerX << std::endl;
}

double Polygon::findSectionLength(double x1, double x2, double y1, double y2) {
    double value1 = std::pow((x2 - x1), 2);
    double value2 = std::pow((y2 - y1), 2);

    return std::pow(value1 + value2, 0.5);
}

void Polygon::setCircuit() {
    std::vector<double>::iterator it;
    std::vector<double> vectorAllXLeft;
    std::vector<double> vectorAllYLeft;
    std::vector<double> vectorAllXRight;
    std::vector<double> vectorAllYRight;

    std::vector<double> vecX = this->vectorX;
    std::vector<double> vecY = this->vectorY;


        vecX.push_back(vecX[0]);
        vecY.push_back(vecY[0]);

        for (int i = 0; i < vecY.size(); i++) {
            if (vecY[i] < this->minLocal && vecY[i + 1] > this->maxLocal && vecY[i + 1] < vecY[i]) {
                vectorAllXLeft.push_back(vecX[i]);
                vectorAllYLeft.push_back(vecY[i]);
            } else if (vecY[i] < this->minLocal && vecY[i] > this->maxLocal && vecY[i + 1] < vecY[i]) {
                vectorAllXLeft.push_back(vecX[i]);
                vectorAllYLeft.push_back(vecY[i]);
            }
            if (vecY[i] > this->maxLocal && vecY[i + 1] < this->minLocal && vecY[i + 1] > vecY[i]) {
                vectorAllXRight.push_back(vecX[i]);
                vectorAllYRight.push_back(vecY[i]);
            } else if (vecY[i] > this->maxLocal && vecY[i] < this->minLocal && vecY[i + 1] > vecY[i]) {
                vectorAllXRight.push_back(vecX[i]);
                vectorAllYRight.push_back(vecY[i]);
            }
        }

//    std::cout << "Wektor X lewy:" << std::endl;
//    for (it = vectorAllXLeft.begin(); it != vectorAllXLeft.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y lewy: " << std::endl;
//    for (it = vectorAllYLeft.begin(); it != vectorAllYLeft.end(); ++it) {
//        std::cout << *it << " ";
//    }
//
//    std::cout << "Wektor X prawy:" << std::endl;
//    for (it = vectorAllXRight.begin(); it != vectorAllXRight.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << "\nWektor Y prawy: " << std::endl;
//    for (it = vectorAllYRight.begin(); it != vectorAllYRight.end(); ++it) {
//        std::cout << *it << " ";
//    }

        this->circuit = 0;


        this->circuit = this->circuit +
                        this->findSectionLength(this->topLeftCornerX, this->topRightCornerX, this->minLocal,
                                                this->minLocal);
        this->circuit = this->circuit +
                        this->findSectionLength(this->bottomLeftCornerX, this->bottomRightCornerX, this->maxLocal,
                                                this->maxLocal);

        if (vectorAllXLeft.empty()) {
            this->circuit = this->circuit +
                            this->findSectionLength(this->topLeftCornerX, this->bottomLeftCornerX, this->minLocal,
                                                    this->maxLocal);
        } else if (vectorAllXLeft.size() == 1) {
            this->circuit = this->circuit +
                            this->findSectionLength(this->topLeftCornerX, vectorAllXLeft.front(), this->minLocal,
                                                    vectorAllYLeft.front()) +
                            this->findSectionLength(vectorAllXLeft.front(), this->bottomLeftCornerX,
                                                    vectorAllYLeft.front(),
                                                    this->maxLocal);
        } else {
            this->circuit = this->circuit +
                            this->findSectionLength(this->topLeftCornerX, vectorAllXLeft.front(), this->minLocal,
                                                    vectorAllYLeft.front());
            for (int i = 0; i < vectorAllXLeft.size() - 1; i++) {
                this->circuit = this->circuit +
                                this->findSectionLength(vectorAllXLeft[i], vectorAllXLeft[i + 1], vectorAllYLeft[i],
                                                        vectorAllYLeft[i + 1]);
            }
            this->circuit = this->circuit +
                            this->findSectionLength(vectorAllXLeft.back(), this->bottomLeftCornerX,
                                                    vectorAllYLeft.back(),
                                                    this->maxLocal);
        }


        if (vectorAllXRight.empty()) {
            this->circuit = this->circuit +
                            this->findSectionLength(this->bottomRightCornerX, this->topRightCornerX, this->maxLocal,
                                                    this->minLocal);
        } else if (vectorAllXRight.size() == 1) {
            this->circuit = this->circuit +
                            this->findSectionLength(this->bottomRightCornerX, vectorAllXRight.front(), this->maxLocal,
                                                    vectorAllYRight.front()) +
                            this->findSectionLength(vectorAllXRight.front(), this->topRightCornerX,
                                                    vectorAllYRight.front(),
                                                    this->minLocal);
        } else {
            this->circuit = this->circuit +
                            this->findSectionLength(this->bottomRightCornerX, vectorAllXRight.front(), this->maxLocal,
                                                    vectorAllYRight.front());
            for (int i = 0; i < vectorAllXRight.size() - 1; i++) {
                this->circuit = this->circuit +
                                this->findSectionLength(vectorAllXRight[i], vectorAllXRight[i + 1], vectorAllYRight[i],
                                                        vectorAllYRight[i + 1]);
            }
            this->circuit = this->circuit +
                            this->findSectionLength(vectorAllXRight.back(), this->topRightCornerX,
                                                    vectorAllYRight.back(),
                                                    this->minLocal);
        }


    std::cout << "Obwód: " << this->circuit << std::endl;
}

void Polygon::printOutput() {
    if(this->checkNucleus()) {
        std::cout << "Jądro istnieje" << std::endl;
    } else {
        std::cout << "Brak jądra" << std::endl;
        std::cout << "Min lokalne: " << this->minLocal << " Max lokalne: " << this->maxLocal << std::endl;
        return;
    }
    std::cout << "Min lokalne: " << this->minLocal << " Max lokalne: " << this->maxLocal << std::endl;
    this->setBottomLeftCornerX();
    this->setBottomRightCornerX();
    this->setTopRightCornerX();
    this->setTopLeftCornerX();
    this->setCircuit();
}