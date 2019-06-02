#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include "Point.cpp"
#define SIZE 10

using namespace std;

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec);
vector<vector<double>> createDistMatrix(vector<Point> points);
double calculateDistance(Point a, Point b);
void printMatrix(vector<vector<double>> dMatrix);
void fillMemoVector(vector<vector<double>>* memo, int size);
void setup(vector<vector<double>> distances, vector<vector<double>>* memo, int startingNode, int size);
void combinations(int r, int n, vector<int32_t>* combinations);
void generateCombinations(int set, int at, int r, int n, vector<int>* subsets);
bool bitNotSet(int element, int subset);
void solve(vector<vector<double>> distances, vector<vector<double>>* memo, int startingNode, int size);
double findMinCost(vector<vector<double>> distances, vector<vector<double>> memo, int startingNode, int size);
vector<int> findOptimalTour(vector<vector<double>> distances, vector<vector<double>> memo, int startingNode, int size);

int main() {

    double tab1[] = {5, 1, 7, 2.2, 4};
    double tab2[] = {2, 2, 6.5, 1, 2.6};

    int size = sizeof(tab1)/sizeof(tab1[0]);

    vector<Point> points;
    fillVector(tab1, tab2, size, &points);
    vector<vector<double >> dMatrix = createDistMatrix(points);
    printMatrix(dMatrix);

    vector<vector<double>> memo;
    fillMemoVector(&memo, dMatrix.size());
    //printMatrix(memo);

    setup(dMatrix, &memo, 0, dMatrix.size());
    printMatrix(memo);

    solve(dMatrix, &memo, 0, dMatrix.size());
    printMatrix(memo);

    cout << "\n\n";

    double minCost;
    minCost = findMinCost(dMatrix, memo, 0, dMatrix.size());
    cout << "Koszt: " <<  minCost << endl;

    vector<int> optimalTour;
    optimalTour = findOptimalTour(dMatrix, memo, 0, dMatrix.size());

    cout << "Ścieżka: [";
    for(int i=0; i<optimalTour.size() - 1; i++) {
        cout << optimalTour[i] << ", ";
    }
    cout << optimalTour.back() << "]\n";

    return 0;
}

vector<int> findOptimalTour(vector<vector<double>> distances, vector<vector<double>> memo, int startingNode, int size) {

    int lastIndex = startingNode;
    int END_STATE = (1 << size) - 1;
    int state = END_STATE;
    vector<int> tour;

    tour.push_back(startingNode);

    for(int i = 1; i < size; i++) {

        int index = -1;
        for(int j = 0; j < size; j++ ) {
            if(j == startingNode || bitNotSet(j, state)) continue;
            if(index == -1) index = j;
            double prevDist = memo[index][state] + distances[index][lastIndex];
            double newDist = memo[j][state] + distances[j][lastIndex];
            if(newDist < prevDist) {
                index = j;
            }
        }
        tour.push_back(index);
        state = state ^ (1 << index);
        lastIndex  = index;
    }

    tour.push_back(startingNode);
    reverse(tour.begin(), tour.end());

    return tour;
}

double findMinCost(vector<vector<double>> distances, vector<vector<double>> memo, int startingNode, int size) {
    int END_STATE = (1 << size) - 1;
    double minTourCost = INFINITY;
    double tourCost;

    for(size_t i = 0; i < size; i++) {
        if(i == startingNode) continue;

        tourCost = memo.at(i).at(END_STATE) + distances.at(i).at(startingNode);
        if(tourCost < minTourCost) {
            minTourCost = tourCost;
        }
    }

    return minTourCost;
}

void solve(vector<vector<double>> distances, vector<vector<double>>* memo, int startingNode, int size) {

    for(size_t n = 3; n <= size; n++) {
        vector<int> combinationsVector;
        combinations(n, size, &combinationsVector);

        for(int subsetIndex = 0; subsetIndex < combinationsVector.size(); subsetIndex++) {
            int32_t subset = combinationsVector[subsetIndex];
            if(bitNotSet(startingNode, subset)) continue;
            for(int next = 0; next < size; next++) {
                cout << "Next: " << next << "\t Not in: " << bitNotSet(next, subset) << endl;
                if(next == startingNode || bitNotSet(next, subset)) continue;
                cout << "Subset: " << subset << "\t1 << next: " << next << "\t";
                int subWithoutNext = subset ^ (1 << next);
                cout << subWithoutNext << endl;
                double minDist = INFINITY;
                for(int end = 0; end < size; end++) {
                    if(end == startingNode || end == next || bitNotSet(end, subset)) continue;
                    double newDist = memo->at(end)[subWithoutNext] + distances[end][next];
                    if(newDist < minDist) {
                        minDist = newDist;
                    }
                }
                memo->at(next)[subset] = minDist;
            }
        }
        cout << endl << "n: " << n << endl;
    }


}

void combinations(int r, int n, vector<int32_t>* combinations) {
    vector<int32_t> subsets;
    generateCombinations(0,0,r,n,&subsets);
    *combinations = subsets;
}

void generateCombinations(int32_t set, int at, int r, int n, vector<int32_t>* subsets) {

    int elementsLeftToPick = n - at;
    if(elementsLeftToPick < r) return;


    if(r == 0) {
        subsets->push_back(set);
    } else {
        for(size_t i = at; i < n; i++) {

            set ^= ( 1 << i );

            generateCombinations(set, i+1, r - 1, n, subsets);

            set ^= ( 1 << i );
        }
    }
}

bool bitNotSet(int element, int subset) {
    return ((1 << element) & subset) == 0;
}

void setup(vector<vector<double>> distances, vector<vector<double>>* memo, int startingNode, int size) {
    for(size_t i=0; i<size; i++) {

        if(i == startingNode) continue;

        memo->at(i).at(1 << startingNode | 1 << i) = distances[startingNode][i];

    }
}

void fillMemoVector(vector<vector<double>>* memo, int size) {

    vector<double> memoRow;

    for(size_t i=0; i<size; i++) {
        for(size_t j=0; j<(1 << size); j++) {
            memoRow.push_back(NULL);
        }
        memo->push_back(memoRow);
        memoRow.clear();
    }

}

void fillVector(const double *tab1, const double *tab2, int size, vector<Point> *vec){
    Point temp;

    for(size_t i=0; i<size; i++) {
        temp.setX(tab1[i]);
        temp.setY(tab2[i]);
        vec->push_back(temp);
    }
}

double calculateDistance(Point a, Point b) {
    double x1 = a.getX();
    double x2 = b.getX();
    double y1 = a.getY();
    double y2 = b.getY();
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

vector<vector<double>> createDistMatrix(vector<Point> points) {

    vector<double> matrixRow;
    vector<vector<double>> dMatrix;

    for(size_t i=0; i<points.size(); i++) {
        for(size_t j=0; j<points.size(); j++) {
            double distance = calculateDistance(points.at(i), points.at(j));
            matrixRow.push_back(distance);
            cout << "i: " << i << "\tj: " << j  << "\tdist: " << distance << endl;
        }
        dMatrix.push_back(matrixRow);
        matrixRow.clear();
    }
    cout << "\n\n";

    return dMatrix;
}

void printMatrix(vector<vector<double>> matrix) {

    cout << "\n\n";

    cout << left << setw(5) << "N";
    for(size_t i=0; i<matrix.at(0).size(); i++) {
        cout << right <<  setw(12) << i;
    }

    cout << "\n";

    for(size_t i=0; i<matrix.size(); i++) {
        cout << left <<  setw(5) << i;
        for(size_t j=0; j<matrix.at(i).size(); j++) {
            cout << right <<  setw(12) << matrix[i][j];
        }
        cout << "\n";
    }

}