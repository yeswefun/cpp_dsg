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

class SecurityFacade {
public:
    // Camera* pCamera = new Camera;
    // Light* pLight = new Light;
    // Sensor* pSensor = new Sensor;
    // Alarm* pAlarm = new Alarm;
    // SecurityFacade(Camera *pCamera, Light *pLight, Sensor *pSensor, Alarm *pAlarm) 
    // : m_camera(pCamera), m_light(pLight), m_sensor(pSensor), m_alarm(pAlarm) {
    // }
    SecurityFacade() {
        cout << "------------> initialize" << endl;
        m_camera = new Camera;
        m_light = new Light;
        m_sensor = new Sensor;
        m_alarm = new Alarm;
    }

    ~SecurityFacade() {
        cout << "------------> cleanup" << endl;
        delete m_camera;
        delete m_light;
        delete m_sensor;
        delete m_alarm;
    }

    void active() {
        cout << "************ system start" << endl;
        m_camera->turnOn();
        m_light->turnOn();
        m_sensor->active();
        m_alarm->active();
    }

    void deactive() {
        cout << "************ system exit" << endl;
        m_camera->turnOff();
        m_light->turnOff();
        m_sensor->deactive();
        m_alarm->deactive();
    }
private:
    Camera* m_camera;
    Light* m_light;
    Sensor* m_sensor;
    Alarm* m_alarm;
};


/*
LOD:
    迪米特法则 / 最少知识原则
*/
int main() {

    SecurityFacade facade;
    facade.active();
    facade.deactive();

    return 0;
}
