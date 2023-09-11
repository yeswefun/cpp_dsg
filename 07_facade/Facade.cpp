#include <iostream>

using namespace std;

class Camera {
public:
    void turnOn() {
        cout << "camera start" << endl;
    }

    void turnOff() {
        cout << "camera exit" << endl;
    }
};

class Light {
public:
    void turnOn() {
        cout << "light start" << endl;
    }
    void turnOff() {
        cout << "light exit" << endl;
    }
};

class Sensor {
public:
    void active() {
        cout << "sensor start" << endl;
    }

    void deactive() {
        cout << "sensor exit" << endl;
    }
};

class Alarm {
public:
    void active() {
        cout << "alarm start" << endl;
    }
    void deactive() {
        cout << "alarm exit" << endl;
    }
};


/*
LOD:
    迪米特法则 / 最少知识原则
*/
int main() {

    Camera* pCamera = new Camera;
    Light* pLight = new Light;
    Sensor* pSensor = new Sensor;
    Alarm* pAlarm = new Alarm;

    cout << "************ system start" << endl;
    pCamera->turnOn();
    pLight->turnOn();
    pSensor->active();
    pAlarm->active();

    cout << "************ system exit" << endl;
    pCamera->turnOff();
    pLight->turnOff();
    pSensor->deactive();
    pAlarm->deactive();

    return 0;
}
