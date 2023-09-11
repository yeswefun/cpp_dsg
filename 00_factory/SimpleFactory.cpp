
#include <iostream>
#include <string>

using namespace std;


class Api {
public:
    virtual void test(string s) = 0;
protected:
    //屏蔽构造，体现接口
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

    return 0;
}
