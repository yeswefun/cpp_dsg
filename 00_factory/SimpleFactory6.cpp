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

class AutoFactory {
public:
    static Api* createApi() {
        Api *pApi = nullptr;
        pApi = static_cast<Api*>(CObjFactory::createObject("ImplOne"));
        return pApi;
    }
};

/*
//TODO: 从配置文件中读取 类名
*/
int main() {
    Api *pApi = AutoFactory::createApi();
    pApi->test("测试");
    return 0;
}
