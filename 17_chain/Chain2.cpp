#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//抽象类
class Handler {
public:
    Handler() : m_next(nullptr) {}

    void setNext(Handler *next) {
        m_next = next;
    }

    int handleRequest(double fee) {
        if (handle(fee)) {
            cout << "ok" << endl;
            return 1;
        } else {
            if (m_next != nullptr) {
                return m_next->handleRequest(fee);
            } else {
                return 0;
            }
        }
    }

    virtual int handle(double fee) = 0;

protected:
    Handler *m_next;
};


class PmHandler : public Handler {
public:
    int handle(double fee) {
        cout << "pm: " << fee << endl;
        return fee >= 0 && fee < 500;
    }
};

class DmHandler : public Handler {
public:
    int handle(double fee) {
        cout << "dm: " << fee << endl;
        return fee >= 500 && fee < 1000;
    }
};

class CeoHandler : public Handler {
public:
    int handle(double fee) {
        cout << "ceo: " << fee << endl;
        return fee >= 1000;
    }
};

/*
过滤器
    权限检查
    数据校验

事件冒泡
    GUI

责任链
*/
int main() {

    Handler *p1 = new PmHandler;
    Handler *p2 = new DmHandler;
    Handler *p3 = new CeoHandler;

    p1->setNext(p2);
    p2->setNext(p3);
    
    //从第一个开始依次处理
    cout << "***************************" << endl;
    cout << p1->handleRequest(-128) << endl;
    cout << "***************************" << endl;
    cout << p1->handleRequest(128) << endl;
    cout << "***************************" << endl;
    cout << p1->handleRequest(512) << endl;
    cout << "***************************" << endl;
    cout << p1->handleRequest(1024) << endl;

    return 0;
}
