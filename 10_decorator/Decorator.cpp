#include <iostream>

using namespace std;


class Beverage {
public:
    virtual double charge() = 0;
};

class Mocha : public Beverage {

};

class GreenTea : public Beverage {
public:
    double charge() {
        return 8;
    }
};

class RedTea : public Beverage {
public:
    double charge() {
        return 10;
    }
};

class IceRedTea : public RedTea {
public:
    double charge() {
        return 4 + RedTea::charge();
    }
};



/*

组合 大于 继承

class HalfGreenHalfRed;
class HalfMilkHalfMocha;
...
*/
int main() {

    IceRedTea irt;
    cout << "charge: " << irt.charge() << endl;

    return 0;
}
