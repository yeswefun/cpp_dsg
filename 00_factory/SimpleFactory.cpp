#include <iostream>
#include <string>

using namespace std;


class Api {
public:
    //具体子类必须重写，抽象子类可以不重写
    virtual void test(string s) = 0;
protected:
    //屏蔽构造函数，体现接口，类外无法访问，子类可以访问
    Api() {}
};


class Impl : public Api {
public:
    void test(string s) {
        cout << "Impl#test: s -> " << s << endl;
    }
};


int main() {

    Api *pApi = new Impl();
    pApi->test("测试");
    delete pApi;

    return 0;
}
