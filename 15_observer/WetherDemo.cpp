#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual void update(string temp, string humi) = 0;
protected:
    Observer() {}
};

class Subject {
public:
    virtual void registerObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
    virtual void notifyObserver() = 0;
protected:
    Subject() {}
};

class WeatherData : public Subject {
public:
    WeatherData(string temp, string humi) : m_temp(temp), m_humi(humi) {}

    void registerObserver(Observer *o) {
        m_observers.push_back(o);
        //notifyObserver();  // 每次注册，都让 所有的observer 得到更新
        o->update(m_temp, m_humi); // 实现每次注册，都让 当前的observer 得到更新，而不影响其它的
    }
    void removeObserver(Observer *o) {
        auto it = find(m_observers.begin(), m_observers.end(), o);
        if (it != m_observers.end()) {
            m_observers.erase(it);
        }
    }
    void notifyObserver() {
        for (vector<Observer*>::iterator it = m_observers.begin(); it != m_observers.end(); it++) {
            (*it)->update(m_temp, m_humi);
        }
    }

    void setData(string temp, string humi) {
        m_temp = temp;
        m_humi = humi;
        notifyObserver();
    }
private:
    vector<Observer*> m_observers;
    string m_temp; // 温度
    string m_humi; // 湿度
};



class PCObserver : public Observer {
public:
    PCObserver(WeatherData *o) {
        m_pWeatherData = o;
        m_pWeatherData->registerObserver(this);
    }

    void update(string temp, string humi) {
        cout << "pc, temp: " << temp << ", humi: " << humi << endl;
    }
private:
    WeatherData *m_pWeatherData;
};

class MobileObserver : public Observer {
public:
    MobileObserver(WeatherData *o) {
        m_pWeatherData = o;
        m_pWeatherData->registerObserver(this);
    }

    void update(string temp, string humi) {
        cout << "mobile, temp: " << temp << ", humi: " << humi << endl;
    }
private:
    WeatherData *m_pWeatherData;
};


int main() {
    
    WeatherData *pwd = new WeatherData("11C", "22%");

    PCObserver pc(pwd);
    MobileObserver moblie(pwd);

    cout << "--------------- 1" << endl;
    pwd->setData("33C", "44%");

    cout << "--------------- 2" << endl;
    pwd->setData("55C", "66%");

    cout << "--------------- 3" << endl;
    pwd->removeObserver(&pc);
    pwd->setData("77C", "88%");
    return 0;
}