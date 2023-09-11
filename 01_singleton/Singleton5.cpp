#include <iostream>
#include <map>

using namespace std;

const static int NUM_MAX = 5;
class Singleton;
static std::map<int, Singleton*> myMap = std::map<int, Singleton*>();


class Singleton {
private:
    Singleton() {
        cout << "构造一个 Singleton 对象: " << this << endl;
    }
public:
    static Singleton* getInstance() {
        instance = myMap[instance_count];
        if (instance == nullptr) {
            instance = new Singleton;
            myMap[instance_count] = instance;
        }
        instance_count++;
        if (instance_count > NUM_MAX) {
            instance_count = 1;
        }
        return instance;
    }
private:
    static Singleton *instance;
    //存放实例个数
    static int instance_count;
    //非静态成员 以 m_ 作为前缀
    //静态成员 以 s_ 作为前缀
    //全局变量 以 g_ 作为前缀
};

Singleton* Singleton::instance = nullptr;
int Singleton::instance_count = 1;

int main() {
    for (int j = 0; j < 5; j++) {
        cout << "********* loop: " << j << endl;
        for (int x = 0; x < 5; x++) {
            Singleton *p = Singleton::getInstance();
            cout << p << endl;
        }
    }
    return 0;
}
