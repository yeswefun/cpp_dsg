#include <iostream>

using namespace std;

class TestSuit {
public:
    virtual void beforeRun() {}
    virtual void afterRun() {}
    virtual void run() = 0;

    //模板方法控制
    void test() {
        beforeRun();
        run();
        afterRun();
    }
};

class Target : public TestSuit {
public:
    void beforeRun() {
        cout << "****************** beforeRun" << endl;
    }
    void afterRun() {
        cout << "****************** afterRun" << endl;
    }
    void run() {
        cout << "run" << endl;
    }
};

/*
好莱坞法则: 不要来找我们，我们会联系你

钩子函数

单元测试工具gtest
    https://github.com/google/googletest
*/
int main() {

    TestSuit *t = new Target();
    
    t->test();

    return 0;
}
