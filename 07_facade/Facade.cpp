#include <iostream>

using namespace std;

class Camera {
public:
    void turnOn() {
        cout << "turn on: camera" << endl;
    }

    void turnOff() {
        cout << "turn off: camera" << endl;
    }
};

class Light {
public:
    void turnOn() {
        cout << "turn on: light" << endl;
    }
    void turnOff() {
        cout << "turn off: light" << endl;
    }
};

class Sensor {
public:
    void active() {
        cout << "turn on: sensor" << endl;
    }

    void deactive() {
        cout << "turn off: sensor" << endl;
    }
};

class Alarm {
public:
    void active() {
        cout << "turn on: alarm" << endl;
    }
    void deactive() {
        cout << "turn off: alarm" << endl;
    }
};


/*
LOD: The Law of Demeter or principle of least knowledge
    迪米特法则 / 最少知识原则
*/
int main() {

    Camera* pCamera = new Camera;
    Light* pLight = new Light;
    Sensor* pSensor = new Sensor;
    Alarm* pAlarm = new Alarm;

    cout << "******************** system start" << endl;
    pCamera->turnOn();
    pLight->turnOn();
    pSensor->active();
    pAlarm->active();

    cout << "******************** system exit" << endl;
    pCamera->turnOff();
    pLight->turnOff();
    pSensor->deactive();
    pAlarm->deactive();

    return 0;
}
