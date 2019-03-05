#include "Polygon.cpp"

int main() {
    //double arrX[] = {3, 4, 5, 6,6,5,4,2,1,2};
    //double arrY[] = {1,3,1,3,5,6,5,6,5,3};

    //double arrX[] = { 11, 16, 13, 15, 12, 11, 10, 4, 7, 7, 10};
    //double arrY[] = { 2, 5, 9, 11, 13, 7, 13, 4, 6, 2, 5};

    double arrX[] = {5, 6, 7, 8, 9, 12, 10, 12, 10, 8, 7, 4, 5, 3, 5, 3};
    double arrY[] = {3, 5, 3, 4, 3, 6, 8, 9, 13, 10, 13, 12, 11, 9, 8, 7};

    //double arrX[] = {1,2,3,3,1};
    //double arrY[] = {2,4,1,6,7};
    //double arrX[] = {1,2,3,2};
    //double arrY[] = {2,4,1,7};
    //double arrX[] = {3,5,5,3};
    //double arrY[] = {2,4,8,6};
    //double arrX[] = {15, 20, 20, 18, 16, 15};
    //double arrY[] = {2, 2, 6, 4, 4, 6};

    std::cout << "Rozmiar tab x: " << (sizeof(arrX)/sizeof(*arrX)) << " Rozmiar tab y: " << (sizeof(arrY)/sizeof(*arrY)) << std::endl;

    std::vector<double > vectorOfX (arrX, arrX + sizeof(arrX) / sizeof(double));
    std::vector<double > vectorOfY (arrY, arrY + sizeof(arrY) / sizeof(double));

    Polygon polygon(vectorOfX, vectorOfY);
    polygon.printOutput();
//    polygon.setTopRightCornerX();
//    polygon.setTopLeftCornerX();
//    polygon.setBottomLeftCornerX();
//    polygon.setBottomRightCornerX();
//    polygon.setCircuit();


    return 0;
}