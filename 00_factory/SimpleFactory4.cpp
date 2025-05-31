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


class ImplOneHelper {
public:
    ImplOneHelper() {
        CObjFactory::registerClass("ImplOne", ImplOneHelper::createObjFunc);
    }

    // 返回值: void*
    static void* createObjFunc() {
        return new ImplOne;
    }
};


int main() {
    ImplOne *pApi = static_cast<ImplOne*>(ImplOneHelper::createObjFunc());
    pApi->test("测试");
    return 0;
}
