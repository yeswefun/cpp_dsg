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

class SecurityFacade {
public:
    // Camera* pCamera = new Camera;
    // Light* pLight = new Light;
    // Sensor* pSensor = new Sensor;
    // Alarm* pAlarm = new Alarm;
    //
    // SecurityFacade(Camera *pCamera, Light *pLight, Sensor *pSensor, Alarm *pAlarm) 
    // : m_camera(pCamera), m_light(pLight), m_sensor(pSensor), m_alarm(pAlarm) {
    // }
    SecurityFacade() {
        cout << "-----------> initialize" << endl;
        m_camera = new Camera;
        m_light = new Light;
        m_sensor = new Sensor;
        m_alarm = new Alarm;
    }

    ~SecurityFacade() {
        cout << "-----------> cleanup" << endl;
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
LOD: The Law of Demeter or principle of least knowledge
    迪米特法则 / 最少知识原则

门面(外观)模式
*/
int main() {

    SecurityFacade facade;
    
    facade.active();
    
    facade.deactive();

    return 0;
}
