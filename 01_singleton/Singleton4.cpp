#include <iostream>
#include <map>

using namespace std;

class Singleton;

static std::map<string, Singleton*> myMap = std::map<string, Singleton*>();

//懶汉 - 延迟加载
class Singleton {
private:
    Singleton() {
        instance = nullptr;
        cout << "构造一个 Singleton 对象: " << this << endl;
    }
public:
    static Singleton* getInstance() {
        //std::map<std::string, int>::iterator it = myMap.find(DEFAULT_KEY);
        if (myMap.find(DEFAULT_KEY) != myMap.end()) {
            return myMap.find(DEFAULT_KEY)->second;
        }
        if (instance == nullptr) {
            instance = new Singleton;
            myMap[DEFAULT_KEY] = instance;
        }
        return instance;
    }
private:
    static Singleton *instance;
    static string DEFAULT_KEY;
};

Singleton* Singleton::instance = nullptr;
string Singleton::DEFAULT_KEY = "One";


int main() {
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    return 0;
}
