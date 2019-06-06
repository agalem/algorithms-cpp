#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

void printVector(vector<double> vec);
void fillVectorWithValue(const double *tab, int size, vector<double>* inputVector);
vector<double>::iterator findBiggestSmallest(vector<double> vec, double value);

void scal(vector<double> currentVector, double elemToAdd, vector<double>* outputVector);
void trim(vector<double> inputVector, double delta, vector<double>* outputVector);
void deleteBigger(vector<double> inputVector, double searchedLength,vector<double>* outputVector);
double subsetSum(vector<double> inputVector, double delta, double searchedLength);

int main() {

   //double elementsTab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //double elementsTab[] = {10, 30, 31, 32};
    double elementsTab[] = {pow(2, 1), pow(2, 2), pow(2, 3), pow(2, 4), pow(2, 5), pow(2, 6), pow(2, 7), pow(2, 8), pow(2, 9), pow(2, 10), pow(2, 11), pow(2, 12), pow(2, 13), pow(2, 14), pow(2, 15)};
    int size = sizeof(elementsTab)/sizeof(elementsTab[0]);

    vector<double> values;
    fillVectorWithValue(elementsTab, size, &values);

    double searchedLength = 10000;
    double delta  = (0.1);

//    cout << "Podaj wartość delta: ";
//    cin >> delta;
//
//    cout << "Podaj szukaną długość: ";
//    cin >> searchedLength;

    cout << endl << endl;

    double answer = subsetSum(values, delta, searchedLength);

    if(answer == 0) {
        cout << "Podano za niską szukaną wartość" << endl;
    } else {
        cout << "\nZnaleziona wartość: " << answer;
    }

    return 0;
}



void scal(vector<double> currentVector, double elemToAdd, vector<double>* outputVector) {

    vector<double>::iterator it;

    for(size_t i = 0; i < currentVector.size(); i++) {
        double sum = currentVector[i] + elemToAdd;
        it = find(currentVector.begin(), currentVector.end(), sum);
        if(it != currentVector.end()) continue;

        outputVector->push_back(sum);
    }

}

void trim(vector<double> inputVector, double delta, vector<double>* outputVector) {

    outputVector->clear();
    outputVector->push_back(inputVector.front());

    double tmp = inputVector[0];

    for(size_t i = 1; i < inputVector.size(); i++) {
        if(tmp < ((1 - delta) * inputVector[i])) {
            outputVector->push_back(inputVector[i]);
            tmp = inputVector[i];
        }
    }
}

void deleteBigger(vector<double> inputVector, double searchedLength,vector<double>* outputVector) {

    outputVector->clear();
    for(auto&& elem: inputVector) {
        if(elem <= searchedLength) {
            outputVector->push_back(elem);
        }
    }

}

double subsetSum(vector<double> inputVector, double delta, double searchedLength) {

    vector<double> scalVec;
    scalVec.push_back(0);

    vector<double> trimedVec;
    vector<double> inRange;

    vector<vector<int>> allIndexes;

    for(size_t i = 0; i < inputVector.size(); i++) {
        scal(scalVec, inputVector[i], &scalVec);
        sort(scalVec.begin(), scalVec.end());
        trim(scalVec, delta, &trimedVec);
        deleteBigger(trimedVec, searchedLength, &inRange);
    }

    printVector(scalVec);
    printVector(trimedVec);
    printVector(inRange);

    cout << "\n\n";

    double answer = inRange.back();


    return answer;

}

vector<double>::iterator findBiggestSmallest(vector<double> vec, double value) {

    vector<double>::iterator it;



    return it;

}


void fillVectorWithValue(const double *tab, int size, vector<double>* inputVector) {
    for(size_t i = 0; i < size; i++ ) {
        inputVector->push_back(tab[i]);
    }
}

void printVector(vector<double> vec) {
    cout << "\n\n";
    for(auto&& elem : vec) {
        cout << left <<  setw(10) << elem;
    }
}
