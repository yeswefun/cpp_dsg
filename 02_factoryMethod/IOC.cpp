
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>

using namespace std;


template<class T>
class IocContainer {
public:
    IocContainer() {}
    ~IocContainer() {}
    
    // 唯一标识 -> 便于查找
    template<class Drived>
    void registerType(string key) {
        std::function<T* ()> creator = [] {return new Drived();};
        registerType(key, creator);
    }

    // 根据唯一的标识去查找对应的构造函数
    T* Resolve(string key) {
        if (creatorMap.find(key) == creatorMap.end()) {
            return nullptr;
        }
        std::function<T* ()> creator = creatorMap[key];
        return creator();
    }

    std::shared_ptr<T> resolveShared(string key) {
        T* ptr = Resolve(key);
        return std::shared_ptr<T>(ptr);
    }

private:
    void registerType(string key, std::function<T* ()> creator) {
        if (creatorMap.find(key) != creatorMap.end()) {
            throw std::invalid_argument("key已经存在: " + key);
        }
        creatorMap.emplace(key, creator);
    }

private:
    map<string, std::function<T* ()>> creatorMap;
};


struct ICar {
    virtual ~ICar() {}
    virtual void test() const = 0;
};

struct Bus : ICar {
    Bus() {}
    void test() const {
        std::cout << "Bus#test" << endl;
    }
};

struct Jeep : ICar {
    Jeep() {}
    void test() const {
        std::cout << "Jeep#test" << endl;
    }
};


int main() {

    IocContainer<ICar> carIOC;
    carIOC.registerType<Bus>("bus");
    carIOC.registerType<Jeep>("jeep");

    std::shared_ptr<ICar> bus = carIOC.resolveShared("bus");
    bus->test();

    std::shared_ptr<ICar> jeep = carIOC.resolveShared("jeep");
    jeep->test();

    return 0;
}
