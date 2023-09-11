#include <iostream>

using namespace std;


class Beverage {
public:
    virtual double charge() = 0;
};

class RedTea : public Beverage {
public:
    double charge() {
        return 10;
    }
};

class GreenTea : public Beverage {
public:
    double charge() {
        return 8;
    }
};

class Mocha : public Beverage {

};

//class HalfGreenHalfRed;
//class HalfMilkHalfMocha;
//...
int main() {

    return 0;
}
