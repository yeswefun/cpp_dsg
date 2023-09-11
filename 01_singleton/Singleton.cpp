#include <iostream>

using namespace std;

class Singleton {
private:
    Singleton() {
        cout << "构造一个 Singleton 对象" << endl;
    }
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton;
        }
        return instance;
    }
private:
    static Singleton *instance;
};

Singleton* Singleton::instance = nullptr;


/*
在 C++ 中，构造函数是非线程安全的
*/
int main() {

    //Singleton *p = new Singleton;
    Singleton *p1 = Singleton::getInstance();
    cout << p1 << endl;

    Singleton *p2 = Singleton::getInstance();
    cout << p2 << endl;

    cout << "*********************" << endl;
    for (int x = 0; x < 8; x++) {
        cout << Singleton::getInstance() << endl;
    }

    return 0;
}
