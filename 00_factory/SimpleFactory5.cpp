#include <iostream>

#include "DynObj2.h"

using namespace std;

class Api {
public:
    virtual void test(string s) = 0;
protected:
    Api() {}
};


//------------------------------------ 客户端不可见: start
class ImplOne : public Api {
public:
    void test(string s) {
        cout << "ImplOne#test: s -> " << s << endl;
    }
};

class ImplTwo : public Api {
public:
    void test(string s) {
        cout << "ImplTwo#test: s -> " << s << endl;
    }
};
//------------------------------------ 客户端不可见: end

REG_CLASS(ImplOne);
REG_CLASS(ImplTwo);

int main() {
    ImplOne *pOne = static_cast<ImplOne*>(CObjFactory::createObject("ImplOne"));
    pOne->test("测试");

    ImplTwo *pTwo = static_cast<ImplTwo*>(CObjFactory::createObject("ImplTwo"));
    pTwo->test("测试");
    return 0;
}
