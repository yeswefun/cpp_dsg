#include <iostream>
#include <string>
#include <memory>

using namespace std;

class IHello {
public:
    IHello() {}
    virtual ~IHello(){}
    virtual void output(const string& msg) = 0;
};

class Hello : public IHello {
public:
    void output(const string &msg) override {
        cout << msg << endl;
    }
};

class HelloProxy : public IHello {
public:
    HelloProxy(IHello *p) : m_p(p) {}
    ~HelloProxy() {
        delete m_p;
        m_p = nullptr;
    }
    void output(const string& msg) final {
        cout << "****************** log before" << endl;
        m_p->output(msg);
        cout << "****************** log after" << endl;
    }
private:
    IHello *m_p;
};

/*
AOP: 面向切面编程
*/
int main() {

    IHello *p1 = new HelloProxy(new Hello());
    p1->output("content1");
    delete p1;

    IHello *p2 = new HelloProxy(new Hello());
    p2->output("content2");
    delete p2;

    IHello *p3 = new HelloProxy(new Hello());
    p3->output("content3");
    delete p3;

    shared_ptr<IHello> ps = make_shared<HelloProxy>(new Hello());
    ps->output("contents");

    return 0;
}

