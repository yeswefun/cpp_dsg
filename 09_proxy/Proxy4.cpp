#include <iostream>
#include <string>
#include <memory>

using namespace std;

class IHello {
public:
    IHello() {}
    virtual ~IHello(){}
    virtual void output(const string& s) = 0;
};

class Hello : public IHello {
public:
    void output(const string &s) override {
        cout << s << endl;
    }
};

class HelloProxy : public IHello {
public:
    HelloProxy(IHello *p) : m_p(p) {}
    ~HelloProxy() {
        delete m_p;
        m_p = nullptr;
    }
    void output(const string& s) final {
        cout << "****************** log before" << endl;
        m_p->output(s);
        cout << "****************** log after" << endl;
    }
private:
    IHello *m_p;
};

/*
AOP: 面向切面编程
*/
int main() {

    IHello *p = new HelloProxy(new Hello());
    p->output("content");

    shared_ptr<IHello> px = make_shared<HelloProxy>(new Hello());
    px->output("content2");

    return 0;
}

