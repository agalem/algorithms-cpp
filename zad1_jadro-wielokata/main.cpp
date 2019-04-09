#include "Polygon.cpp"

int main() {

    //double arrX[] = {0, 2, 2, 5, 5, 6, 6, 4, 4, 3, 3, 0};
    //double arrY[] = {0, 0, 3, 3, 1, 2, 4, 4, 6, 6, 5, 5};

    double arrX[] = {3, 3, 4, 4, 5, 1, 1, 0, 0};
    double arrY[] = {0, 1, 1, 0, 0, 5, 1, 1, 0};

    std::cout << "Rozmiar tab x: " << (sizeof(arrX)/sizeof(*arrX)) << " Rozmiar tab y: " << (sizeof(arrY)/sizeof(*arrY)) << std::endl;

    std::vector<double > vectorOfX (arrX, arrX + sizeof(arrX) / sizeof(double));
    std::vector<double > vectorOfY (arrY, arrY + sizeof(arrY) / sizeof(double));


    Polygon polygon(vectorOfX, vectorOfY);
    polygon.printOutput();


    return 0;
}