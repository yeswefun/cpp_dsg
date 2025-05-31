#include <iostream>
#include <map>

using namespace std;

const static int NUM_MAX = 5;
class Singleton;
static map<int, Singleton*> myMap = map<int, Singleton*>();


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
        // 1, 2, 3, 4, 5, [6]->1
        if (instance_count > NUM_MAX) {
            instance_count = 1;
        }
        return instance;
    }

    static void printInstanceCount() {
        cout << "instance_count: " << instance_count << endl;
    }
private:
    static Singleton *instance;
    static int instance_count; // 存放实例个数
};

Singleton* Singleton::instance = nullptr;
int Singleton::instance_count = 1;

/*
    非静态成员 以 m_ 作为前缀
    静态成员 以 s_ 作为前缀
    全局变量 以 g_ 作为前缀

    多例缓存，多个单例的缓存
*/
int main() {

    cout << "****************** debug-1" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "*** loop: " << i << endl;
        Singleton::printInstanceCount();
        Singleton::getInstance();
        Singleton::printInstanceCount();
    }

    cout << "****************** debug-2" << endl;
    for (int i = 0; i < 6; i++) { // row
        for (int j = 0; j < NUM_MAX; j++) { // column
            Singleton* p = Singleton::getInstance();
            cout << p << " ";
        }
        cout << endl;
    }
    
    return 0;
}
