#include "Car.cpp"

int main() {
    Car car;

    // try to drive 10 times
    for (int i = 0; i < 10; i++) {
        bool didDrive = car.drive();
        if (!didDrive) {
            // car is broken! must fix it
            car.fix();
        }
    }

    return 0;
}