#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Subject;

/*
Member:
Subject1 s1;
Subject2 s2;
...

Method:
void onChange() {
    s1.update(...);
    s2.update(...);
    ...
}
*/
class Observer {
public:
    virtual void onXxxChanged(Subject *o, string msg) = 0;
};

class ClientObserver : public Observer {
public:
    void onXxxChanged(Subject *o, string msg) {
        cout << "onXxxChanged: " << this << " from " << o << ", msg: " << msg << endl;
    }
};


class Subject {
public:
    virtual void addObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
    virtual void notifyXxxChanged(string msg) = 0;
};

class ServerSubject : public Subject {
public:
    void addObserver(Observer *o) {
        m_list.push_back(o);
    }
    void removeObserver(Observer *o) {
        auto it = find(m_list.begin(), m_list.end(), o);
        if (it != m_list.end()) {
            m_list.erase(it);
        }
    }
    void notifyXxxChanged(string msg) {
        for (list<Observer*>::iterator it = m_list.begin(); it != m_list.end(); it++) {
            (*it)->onXxxChanged(this, msg);
        }
    }
private:
    list<Observer*> m_list;
};


/*
当一个对象的状态发生改变的时候，
如何让依赖于它的所有对象得到通知，并进行相应的处理?

订阅-发布 的软件架构
    一对多
*/
int main() {

    Observer *o1 = new ClientObserver;
    Observer *o2 = new ClientObserver;
    Observer *o3 = new ClientObserver;

    Subject *s = new ServerSubject;
    s->addObserver(o1);
    s->addObserver(o2);
    s->addObserver(o3);

    cout << "************************" << endl;
    s->notifyXxxChanged("msg-1");

    cout << "************************" << endl;
    s->removeObserver(o2);
    s->notifyXxxChanged("msg-2");

    return 0;
}
