#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>

using namespace std;

// IocContainer<ICar> carIOC;
template<class T>
class IocContainer {
public:
    IocContainer() {}
    ~IocContainer() {}
    
    // 唯一标识 -> 便于查找
    // carIOC.registerType<Bus>("bus");
    template<class Drived>
    void registerType(string key) {
        function<T* ()> creator = [] {return new Drived();};
        registerType(key, creator);
    }

    // 根据 唯一标识 查找 对应的构造函数
    T* Resolve(string key) {
        if (creatorMap.find(key) == creatorMap.end()) {
            return nullptr;
        }
        function<T* ()> creator = creatorMap[key];
        return creator();
    }

    // shared_ptr<ICar> bus = carIOC.resolveShared("bus");
    shared_ptr<T> resolveShared(string key) {
        T* ptr = Resolve(key);
        return shared_ptr<T>(ptr);
    }

private:
    void registerType(string key, function<T* ()> creator) {
        if (creatorMap.find(key) != creatorMap.end()) {
            throw invalid_argument("key已经存在: " + key);
        }
        creatorMap.emplace(key, creator);
    }

private:
    map<string, function<T* ()>> creatorMap;
};


struct ICar {
    virtual ~ICar() {}
    virtual void test() const = 0;
};

struct Bus : ICar {
    Bus() {}
    void test() const {
        cout << "Bus#test" << endl;
    }
};

struct Jeep : ICar {
    Jeep() {}
    void test() const {
        cout << Jeep::ID << "#test" << endl;
    }
    static const string ID;
};

const string Jeep::ID = "Jeep";


/*
IOC: Inversion of Control

DI: Dependency Injection
*/
int main() {

    IocContainer<ICar> carIOC;
    carIOC.registerType<Bus>("bus");
    carIOC.registerType<Jeep>(Jeep::ID);

    shared_ptr<ICar> bus = carIOC.resolveShared("bus");
    bus->test();

    shared_ptr<ICar> jeep = carIOC.resolveShared(Jeep::ID);
    jeep->test();

    return 0;
}
