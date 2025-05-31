#include <iostream>

#include "DynObj.h"

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


/*
gcc/g++
    -E                       Preprocess only; do not compile, assemble or link.
    -S                       Compile only; do not assemble or link.
    -c                       Compile and assemble, but do not link.
    -o <file>                Place the output into <file>.

    // 预处理
    $ g++ -E test.cpp -o test.i

    // 编译
    $ g++ -S test.i -o test.s

    // 汇编
    $ g++ -c test.s -o test.o

    // 链接
    $ g++ test.o -o test.out
*/
int main() {
    ImplOne *pOne = static_cast<ImplOne*>(CObjFactory::createObject("ImplOne"));
    pOne->test("测试");

    ImplTwo *pTwo = static_cast<ImplTwo*>(CObjFactory::createObject("ImplTwo"));
    pTwo->test("测试");
    return 0;
}
