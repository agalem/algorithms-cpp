#include "Polygon.cpp"

int main() {
    double arrX[] = {3, 4, 5, 6,6,5,4,2,1,2};
    double arrY[] = {1,3,1,3,5,6,5,6,5,3};

    //double arrX[] = {};

    std::cout << "Rozmiar tab x: " << (sizeof(arrX)/sizeof(*arrX)) << " Rozmiar tab y: " << (sizeof(arrY)/sizeof(*arrY)) << std::endl;

    std::vector<double > vectorOfX (arrX, arrX + sizeof(arrX) / sizeof(double));
    std::vector<double > vectorOfY (arrY, arrY + sizeof(arrY) / sizeof(double));

    Polygon polygon(vectorOfX, vectorOfY);
    polygon.printOutput();
    polygon.setTopRightCornerX();

    return 0;
}