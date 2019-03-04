#ifndef CAR_R
#define CAR_R

class Car {
    bool in_working_condition_;
public:
    Car();
    void wearAndTear();
    bool drive();
    void fix();
};

#endif