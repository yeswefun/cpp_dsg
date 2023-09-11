#include <iostream>
#include <string>

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


class Factory {
public:
    static Api* createApi(int type) {
        Api *pApi = nullptr;
        if (type == 1) {
            pApi = new ImplOne();
        } else if (type == 2) {
            pApi = new ImplTwo();
        }
        return pApi;
    }

    static Api* createApi() {
        return new ImplOne();
        //return createApi(1);
    }
};


/*
客户端只看到 Api 和 Factory

通过 接口 隔离 实现

Factory 实现了变化隔离
*/
int main() {
    Api *pApi = Factory::createApi(1);
    pApi->test("测试");

    pApi = Factory::createApi(2);
    pApi->test("测试");

    pApi = Factory::createApi();
    pApi->test("测试");

    return 0;
}
